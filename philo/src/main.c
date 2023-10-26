#include "../philo.h"

static int	initialize_philos(t_philo **philos, int	n_philo);
static int	create_threads(pthread_t *threads,
			t_philo **philos, int n_philo);
static int	join_threads(pthread_t *threads, int n_philo);

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_philo		**philos;
	int		n_philo;

	if (parse(argc, argv))
	{
		printf("%s\n", PARSE_ERR);
		return (1);
	}
	n_philo = ft_atoi(argv[1]);
	threads = (pthread_t *)malloc(n_philo * sizeof(pthread_t));
	if (!threads)
		return (2);
	philos = (t_philo **)malloc(n_philo * sizeof(t_philo *));
	if (!philos)
		return (3);
	if (initialize_philos(philos, n_philo))
		return (4);
	if (create_threads(threads, philos, n_philo))
		return (5);
	if (join_threads(threads, n_philo))
		return (6);
	return (0);
}

static int	initialize_philos(t_philo **philos, int	n_philo)
{
	int		i;
	pthread_mutex_t	*fork_mutex;
	e_dead		*dead;
	e_fork		**forks;

	if (pthread_mutex_init(fork_mutex, NULL))
		return (1);
	dead = (e_dead *)malloc(sizeof(e_dead));
	if (!dead)
		return (1);
	forks = (e_fork **)malloc(n_philo * sizeof(e_fork));
	if (!forks)
		return (1);
	i = -1;
	while (++i < n_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			return (1);
		philos[i] -> id = i;
		philos[i] -> dead = dead;
	}
	return (0);
}

static int	create_threads(pthread_t *threads,
			  t_philo **philos, int	n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_create(&threads[i], NULL, &start, NULL))
			return (1);
	}
	return (0);
}

static int	join_threads(pthread_t *threads, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
	}
	return (0);
}
