#include "philosophers.h"

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