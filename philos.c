#include "philosophers.h"

void	init_philos(char **argv, t_philo *philos, pthread_mutex_t *forks, t_program *program)
{
	int i;
	int num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].start_time = program->start_time;
		philos[i].last_meal = philos[i].start_time;
		philos[i].r_fork = &forks[i];
		if (num_of_philos == 1)
			philos[i].l_fork = NULL;
		else
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