#include "philosophers.h"

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->dead_lock);
	if (!*(philo->dead))
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%lu %d %s", get_time() - philo->start_time, philo->id, message);
		pthread_mutex_unlock(philo->write_lock);	
	}
	pthread_mutex_unlock(philo->dead_lock);
}

void	print_log_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%lu %d is died\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}