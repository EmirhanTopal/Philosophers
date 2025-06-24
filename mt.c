#include "philosophers.h"

void	init_mutex(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->start_time = get_time();
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void	destroy_all_mutex(t_program *program)
{
	int i;
    int num_of_philos;

	i = 0;
	num_of_philos = program->philos[0].num_of_philos;
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
    while (i < num_of_philos)
    {
        pthread_mutex_destroy(program->philos[i].r_fork);
		if (program->philos[i].l_fork != NULL)
			pthread_mutex_destroy(program->philos[i].l_fork);
        i++;
    }
}