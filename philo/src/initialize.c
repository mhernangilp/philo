#include "../philo.h"

static t_common	*initialize_common();

t_philo	*initialize_philos(int n_philo)
{
	t_philo		*philos;
	t_common	*common;
	int		i;

	philos = (t_philo *)malloc(n_philo * sizeof(t_philo));
	if (!philos)
		return (NULL);
	common = initialize_common();
	if (!common)
		return (NULL);
	i = -1;
	while (++i < n_philo)
	{
		philos[i].id = i;
		philos[i].common = common;
		philos[i].r_fork = FREE;
		if (i && i != n_philo - 1)
			philos[i].l_fork = &philos[i - 1].r_fork;
		if (i == n_philo - 1)
			philos[0].l_fork = &philos[i].r_fork;
	}
	return (philos);
}

static t_common	*initialize_common()
{
	t_common	*common;

	common = (t_common *)malloc(sizeof(t_common));
	if (!common)
		return (NULL);
	common -> dead = NO;
	pthread_mutex_init(&common -> fork_mutex, NULL);
	pthread_mutex_init(&common -> die_mutex, NULL);
	pthread_mutex_init(&common -> write_mutex, NULL);
	return (common);
}
