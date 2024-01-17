/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:37:50 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_full(t_philo *philos, int n_philos)
{
	int	i;
	int	full;

	full = 1;
	i = -1;
	pthread_mutex_lock(&philos[0].common -> n_times_mutex);
	while (++i < n_philos)
		if (philos[i].common -> n_eaten[i] < philos[i].common -> n_times_to_eat)
			full = 0;
	pthread_mutex_unlock(&philos[0].common -> n_times_mutex);
	if (full)
	{
		pthread_mutex_lock(&philos[0].common -> die_mutex);
		philos -> common -> dead = YES;
		pthread_mutex_unlock(&philos[0].common -> die_mutex);
	}
	return (full);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo -> common -> ms_mutex);
	if (get_time() - philo -> common -> start_time
		- philo -> ms_eaten > philo -> common -> time_to_die)
	{
		pthread_mutex_unlock(&philo -> common -> ms_mutex);
		pthread_mutex_lock(&philo -> common -> die_mutex);
		pthread_mutex_lock(&philo -> common -> write_mutex);
		philo -> common -> dead = YES;
		printf("%ld %d died\n", get_time()
			- philo -> common -> start_time, philo -> id);
		pthread_mutex_unlock(&philo -> common -> write_mutex);
		pthread_mutex_unlock(&philo -> common -> die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo -> common -> ms_mutex);
	return (0);
}

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}
