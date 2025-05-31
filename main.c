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

void init_mutex(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void init_philos(char **argv, t_philo *philos, pthread_mutex_t *forks, t_program *program)
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
		// start time
		// last eat
		philos[i].r_fork = forks[i];
		philos[i].l_fork = forks[(i + 1) % num_of_philos];
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

int	main(int argc, char **argv)
{
	t_philo philos[200];
	pthread_mutex_t forks[200];
	t_program program;
	int control;


	if (argc == 6 || argc == 5)
	{
		control = control_argv(argv);
		if (!control)
		{
			//exit & free
			return (0);
		}
		init_mutex(&program, &philos);
	}
	else
		return (0);
	
	
}
