#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

int ft_atoi(char *str);

// each philo has that
typedef struct s_philo
{
	pthread_t		thread; // philo thread
	int				id; // philo id
	int				eating; // is philo eating (flag)
	int				meals_eaten; // how many meals did philo eat
	size_t			start_time; // simulation starting time
	size_t			last_meal; // last meal time (timestamp)
	size_t			time_to_die; // parameter time
	size_t			time_to_eat; // parameter time
	size_t			time_to_sleep; // parameter time
	int				num_of_philos; // paramter num of philos
	int				num_times_to_eat; // optional paramter argv[5]
	int				*dead; // it points to the dead_flag in the s_program
	pthread_mutex_t	*r_fork; // right fork mutex pointer
	pthread_mutex_t	*l_fork; // left fork mutex pointer
	pthread_mutex_t	*write_lock; // t_program'dan gelen mutexlerin pointerları.
	pthread_mutex_t	*dead_lock; // t_program'dan gelen mutexlerin pointerları.
	pthread_mutex_t	*meal_lock; // t_program'dan gelen mutexlerin pointerları.
}   t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}   t_program;

#endif