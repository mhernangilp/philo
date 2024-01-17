/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:16 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:49:06 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_fork(t_philo *philo, long int start_time, int mode);

void	ph_eat(t_philo *philo)
{
	long int	start_time;
	long int	eat_st_time;

	start_time = philo -> common -> start_time;
	pthread_mutex_lock(&philo -> l_fork);
	if (!dead(philo))
		take_fork(philo, start_time, 0);
	pthread_mutex_lock(philo -> r_fork);
	if (!dead(philo))
		take_fork(philo, start_time, 1);
	eat_st_time = get_time();
	pthread_mutex_lock(&philo -> common -> ms_mutex);
	philo -> ms_eaten = get_time() - start_time;
	pthread_mutex_unlock(&philo -> common -> ms_mutex);
	if (philo -> common -> n_times_to_eat != -1)
	{
		pthread_mutex_lock(&philo -> common -> n_times_mutex);
		philo -> common -> n_eaten[philo -> id - 1] += 1;
		pthread_mutex_unlock(&philo -> common -> n_times_mutex);
	}
	while (get_time() - eat_st_time < philo -> common -> time_to_eat)
		usleep(500);
	pthread_mutex_unlock(&philo -> l_fork);
	pthread_mutex_unlock(philo -> r_fork);
}

void	ph_sleep(t_philo *philo)
{
	long int	start_time;
	long int	sleep_st_time;

	sleep_st_time = get_time();
	start_time = philo -> common -> start_time;
	if (!dead(philo))
	{
		pthread_mutex_lock(&philo -> common -> write_mutex);
		printf("%ld %d is sleeping\n", get_time() - start_time, philo -> id);
		pthread_mutex_unlock(&philo -> common -> write_mutex);
	}
	while (get_time() - sleep_st_time < philo -> common -> time_to_sleep)
		usleep(500);
}

void	ph_think(t_philo *philo)
{
	long int	start_time;

	start_time = philo -> common -> start_time;
	if (!dead(philo))
	{
		pthread_mutex_lock(&philo -> common -> write_mutex);
		printf("%ld %d is thinking\n", get_time() - start_time, philo -> id);
		pthread_mutex_unlock(&philo -> common -> write_mutex);
	}
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo -> common -> die_mutex);
	if (philo -> common -> dead == NO)
	{
		pthread_mutex_unlock(&philo -> common -> die_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo -> common -> die_mutex);
	return (1);
}

static void	take_fork(t_philo *philo, long int start_time, int mode)
{
	pthread_mutex_lock(&philo -> common -> write_mutex);
	printf("%ld %d has taken a fork\n", get_time() - start_time,
		philo -> id);
	if (mode == 1)
	{
		printf("%ld %d is eating\n", get_time() - start_time,
			philo -> id);
	}
	pthread_mutex_unlock(&philo -> common -> write_mutex);
}
