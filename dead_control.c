#include "philosophers.h"

static 	int help_monitor()
{

}

void	*check_one_dead_monitor(void *philos)
{
	int		i;
	int		num_of_philos;
	int 	num_times_to_eat;
	int		all_meats_eaten;
	long 	time_since_last_meal;
	int		meals;

	t_philo *my_philos = (t_philo *)philos;
	num_of_philos = my_philos[0].num_of_philos;
	num_times_to_eat = my_philos[0].num_times_to_eat;
	while (1)
	{
		all_meats_eaten = 1;
		i = 0;
		pthread_mutex_lock(my_philos->dead_lock);
		if (*(my_philos->dead))
		{
			pthread_mutex_unlock(my_philos->dead_lock);
			return (NULL);
		}
		else
			pthread_mutex_unlock(my_philos->dead_lock);
		while (i < num_of_philos)
		{
			pthread_mutex_lock(my_philos->meal_lock);
			time_since_last_meal = get_time() - my_philos[i].last_meal;
			meals = my_philos[i].meals_eaten;
			pthread_mutex_unlock(my_philos->meal_lock);
			if (my_philos->num_times_to_eat != -1 && meals >= num_times_to_eat)
			{
				i++;
				continue;
			}
			if (time_since_last_meal > my_philos[i].time_to_die)
			{
				pthread_mutex_lock(my_philos->dead_lock);
				*(my_philos->dead) = 1;
				print_log_dead(&my_philos[i]);
				pthread_mutex_unlock(my_philos->dead_lock);
				return (NULL);
			}
			if (my_philos->num_times_to_eat != -1 && meals < num_times_to_eat)
				all_meats_eaten = 0;
			i++;
		}
		if (all_meats_eaten && num_times_to_eat != -1)
		{
			pthread_mutex_lock(my_philos->dead_lock);
			*(my_philos->dead) = 1;
			pthread_mutex_unlock(my_philos->dead_lock);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
