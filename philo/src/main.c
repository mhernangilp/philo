#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <stdlib.h>

static int	create_threads(t_philo *philos, int n_philos);
static int	join_threads(t_philo *philos, int n_philos);
static void	free_all(t_philo *philos);

int	main(int argc, char **argv)
{
	t_philo		*philos;
	int		n_philo;

	if (parse(argc, argv))
	{
		printf("%s\n", PARSE_ERR);
		return (1);
	}
	n_philo = ft_atoi(argv[1]);
	philos = initialize_philos(n_philo);
	if (!philos)
		return (2);
	if (create_threads(philos, n_philo))
		return (3);
	if (join_threads(philos, n_philo))
		return (4);
	free_all(philos);
	return (0);
}

static int	create_threads(t_philo *philos, int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
		if (pthread_create(&philos[i].thread, NULL,
		     &start, &philos[i]))
			return (1);
	return (0);
}

static int	join_threads(t_philo *philos, int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
		if (pthread_join(philos[i].thread, NULL))
			return (1);
	return (0);
}

static void	free_all(t_philo *philos)
{
	pthread_mutex_destroy(&philos -> common -> fork_mutex);
	pthread_mutex_destroy(&philos -> common -> die_mutex);
	pthread_mutex_destroy(&philos -> common -> write_mutex);
	free(philos -> common);
	free(philos);
}
