#include "philosophers.h"

void	create_threads(char **argv, t_philo *philos, pthread_t *observer_thread)
{
	int	i;
	int	num_of_philos;
	
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, philos_routine, (void *)&philos[i]);
		i++;
	}
	pthread_create(observer_thread, NULL, check_one_dead_monitor, philos);
}

void	join_threads(char **argv, t_philo *philos, pthread_t observer)
{
	int	i;
	int	num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(observer, NULL);
}
