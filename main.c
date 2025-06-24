#include "philosophers.h"

static int control_argv(char **argv)
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
			return (0);
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
