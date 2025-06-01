#include "philosophers.h"
#include <unistd.h>

int control_argv(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = ft_atoi(argv[i]);
		if (i == 5 && j >= 0)
		{
			i++;
			continue;
		}
		else if (j <= 0 || (j > 200 && i == 1))
			return (0);
		i++;
	}
	return (1);
}

void	init_mutex(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->start_time = get_time();
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void	init_philos(char **argv, t_philo *philos, pthread_mutex_t *forks, t_program *program)
{
	int i;
	int num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = program->start_time;
		philos[i].last_meal = get_time();
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % num_of_philos];
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].num_of_philos = num_of_philos;
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philos[i].num_times_to_eat = ft_atoi(argv[5]);
		else
			philos[i].num_times_to_eat = -1;
		i++;
	}
}

void	init_forks(char **argv, pthread_mutex_t *forks)
{
	int i;
	int num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_log(philo, "is eating\n");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
void	nap(t_philo *philo)
{
	print_log(philo, "is sleeping\n");
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_log(philo, "is thinking\n");
}

void	*philos_routine(void *arg_philo)
{
	t_philo *my_philo = (t_philo *)arg_philo;
	int i = 0;

	if (my_philo->id % 2 != 0)
	{
		usleep((my_philo->time_to_eat * 1000) / 2);
	}
	while (!*(my_philo->dead))
	{
		eat(my_philo);
		// if (my_philo->num_times_to_eat != -1 && my_philo->meals_eaten >= my_philo->num_times_to_eat)
        //     break;
		if (*(my_philo->dead))
			break;
		nap(my_philo);
		if (*(my_philo->dead))
			break;
		think(my_philo);
	}
	return (NULL);
}

void	*check_one_dead(void *philos)
{
	int		i;
	t_philo *my_philos = (t_philo *)philos;

	int num_of_philos = my_philos[0].num_of_philos;
	while (!*(my_philos->dead))
	{
		i = 0;
		while (i < num_of_philos)
		{
			if ((get_time() - my_philos[i].last_meal) > my_philos[i].time_to_die)
			{
				*(my_philos->dead) = 1;
				pthread_mutex_lock(my_philos->dead_lock);
				print_log_dead(&my_philos[i], "is dead\n");
				pthread_mutex_unlock(my_philos->dead_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	create_threads(char **argv, t_philo *philos, pthread_t *observer_thread)
{
	int 		i;
	int 		num_of_philos;
	
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, philos_routine, (void *)&philos[i]);
		i++;
	}
	pthread_create(observer_thread, NULL, check_one_dead, philos);
}

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->write_lock);
	if (!*(philo->dead))
	{
		printf("%lu %d %s", get_time() - philo->start_time, philo->id, message);
	}
	pthread_mutex_unlock(philo->write_lock);
}

void	print_log_dead(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%lu %d %s", get_time() - philo->start_time, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

void	join_threads(char **argv, t_philo *philos, pthread_t observer)
{
	int i;
	int num_of_philos;
	
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(observer, NULL);
	
}

void	destroy_all_mutex(t_program *program)
{
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	int i = 0;
    int num_of_philos = program->philos[0].num_of_philos;
    while (i < num_of_philos)
    {
        pthread_mutex_destroy(program->philos[i].r_fork);
        pthread_mutex_destroy(program->philos[i].l_fork);
        i++;
    }
}
int	main(int argc, char **argv)
{
	t_philo			philos[200];
	pthread_mutex_t forks[200];
	t_program		program;
	pthread_t		observer_thread;
	int				control;

	
	if (argc == 6 || argc == 5)
	{
		control = control_argv(argv);
		if (!control)
		{
			//exit & free
			return (0);
		}
		init_mutex(&program, philos);
		init_philos(argv, philos, forks, &program);
		init_forks(argv, forks);
		create_threads(argv, philos, &observer_thread);
		join_threads(argv, philos, observer_thread);
		destroy_all_mutex(&program);
	}
	else
		return (0);
}
