/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:30 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:37:32 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	create_threads(t_philo *philos, int n_philos);
static int	join_threads(t_philo *philos, int n_philos);
static void	free_all(t_philo *philos, int n_philos);
static void	p_dead(t_philo *philos, int n_philos);

int	main(int argc, char **argv)
{
	t_philo		*philos;
	int			n_philo;

	if (parse(argc, argv))
	{
		printf("%s\n", PARSE_ERR);
		return (1);
	}
	n_philo = ft_atoi(argv[1]);
	philos = initialize_philos(n_philo, argv);
	if (!philos)
		return (2);
	if (n_philo == 1)
	{
		printf("%d %d died\n", philos -> common -> time_to_die, 1);
		return (0);
	}
	if (create_threads(philos, n_philo))
		return (3);
	p_dead(philos, n_philo);
	if (join_threads(philos, n_philo))
		return (4);
	free_all(philos, n_philo);
	return (0);
}

static void	p_dead(t_philo *philos, int n_philos)
{
	int	dead;
	int	i;

	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < n_philos && !dead)
			if (check_death(&philos[i]))
				dead = 1;
		if (philos[0].common -> n_times_to_eat != -1
			&& check_full(philos, n_philos))
			dead = 1;
	}
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

static void	free_all(t_philo *philos, int n_philos)
{
	int	i;

	pthread_mutex_destroy(&philos -> common -> die_mutex);
	pthread_mutex_destroy(&philos -> common -> write_mutex);
	pthread_mutex_destroy(&philos -> common -> n_times_mutex);
	pthread_mutex_destroy(&philos -> common -> ms_mutex);
	i = -1;
	while (++i < n_philos)
		pthread_mutex_destroy(&philos[i].l_fork);
	free(philos -> common -> n_eaten);
	free(philos -> common);
	free(philos);
}
