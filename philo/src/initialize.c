/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:23 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:37:25 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_common	*initialize_common(char **argv, int philo);

t_philo	*initialize_philos(int n_philo, char **argv)
{
	t_philo			*philos;
	t_common		*common;
	pthread_mutex_t	l_fork;
	int				i;

	philos = (t_philo *)malloc(n_philo * sizeof(t_philo));
	if (!philos)
		return (NULL);
	common = initialize_common(argv, n_philo);
	if (!common)
		return (NULL);
	i = -1;
	while (++i < n_philo)
	{
		philos[i].id = i + 1;
		philos[i].ms_eaten = 0;
		philos[i].common = common;
		pthread_mutex_init(&l_fork, NULL);
		philos[i].l_fork = l_fork;
		if (i != n_philo - 1)
			philos[i].r_fork = &philos[i + 1].l_fork;
		else
			philos[i].r_fork = &philos[0].l_fork;
	}
	return (philos);
}

static t_common	*initialize_common(char **argv, int n_philo)
{
	t_common	*common;

	common = (t_common *)malloc(sizeof(t_common));
	if (!common)
		return (NULL);
	common -> dead = NO;
	common -> time_to_die = ft_atoi(argv[2]);
	common -> time_to_eat = ft_atoi(argv[3]);
	common -> time_to_sleep = ft_atoi(argv[4]);
	common -> n_eaten = (int *)malloc((n_philo + 1) * sizeof(int));
	common -> n_eaten[n_philo] = 0;
	common -> start_time = get_time();
	common -> n_philo = n_philo;
	if (common -> start_time == -1)
		return (NULL);
	if (argv[5])
		common -> n_times_to_eat = ft_atoi(argv[5]);
	else
		common -> n_times_to_eat = -1;
	pthread_mutex_init(&common -> die_mutex, NULL);
	pthread_mutex_init(&common -> write_mutex, NULL);
	pthread_mutex_init(&common -> n_times_mutex, NULL);
	pthread_mutex_init(&common -> ms_mutex, NULL);
	return (common);
}
