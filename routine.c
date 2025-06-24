#include "philosophers.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_log(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_log(philo, "has taken a fork\n");
		if (philo->l_fork == NULL)
		{
			usleep(philo->time_to_die * 1000);
			pthread_mutex_unlock(philo->r_fork);
			return ;
		}
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, "has taken a fork\n");
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_log(philo, "is eating\n");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	int		meals;

	if (my_philo->id % 2 != 0)
		usleep(my_philo->time_to_eat * 100);
	while (1)
	{
		pthread_mutex_lock(my_philo->meal_lock);
		meals = my_philo->meals_eaten;
		pthread_mutex_unlock(my_philo->meal_lock);
		if (my_philo->num_times_to_eat != -1 && meals >= my_philo->num_times_to_eat)
			return (NULL);
		pthread_mutex_lock(my_philo->dead_lock);
		if (*(my_philo->dead))
		{
			pthread_mutex_unlock(my_philo->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(my_philo->dead_lock);
		eat(my_philo);
		nap(my_philo);
		think(my_philo);
	}
	return (NULL);
}