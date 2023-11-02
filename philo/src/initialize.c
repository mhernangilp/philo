#include "../philo.h"
#include <bits/types/struct_timeval.h>

static t_common	*initialize_common(char **argv);

t_philo	*initialize_philos(int n_philo, char **argv)
{
	t_philo		*philos;
	t_common	*common;
	int		i;

	philos = (t_philo *)malloc(n_philo * sizeof(t_philo));
	if (!philos)
		return (NULL);
	common = initialize_common(argv);
	if (!common)
		return (NULL);
	i = -1;
	while (++i < n_philo)
	{
		philos[i].id = i + 1;
		philos[i].n_eaten = 0;
		philos[i].ms_eaten = 0;
		philos[i].common = common;
		philos[i].r_fork = FREE;
		if (i && i != n_philo - 1)
			philos[i].l_fork = &philos[i - 1].r_fork;
		if (i == n_philo - 1)
			philos[0].l_fork = &philos[i].r_fork;
	}
	return (philos);
}

static t_common	*initialize_common(char **argv)
{
	t_common	*common;

	common = (t_common *)malloc(sizeof(t_common));
	if (!common)
		return (NULL);
	common -> dead = NO;
	common -> time_to_die = ft_atoi(argv[2]);
	common -> time_to_eat = ft_atoi(argv[3]);
	common -> time_to_sleep = ft_atoi(argv[4]);
	common -> start_time = get_time();
	if (common -> start_time == -1)
		return (NULL);
	if (argv[5])
		common -> n_times_to_eat = ft_atoi(argv[5]);
	else
		common -> n_times_to_eat = -1;
	pthread_mutex_init(&common -> fork_mutex, NULL);
	pthread_mutex_init(&common -> die_mutex, NULL);
	pthread_mutex_init(&common -> write_mutex, NULL);
	return (common);
}
