#include "../philo.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>

void	check_full(t_philo *philo)
{
	int	i;
	int	finished;

	finished = 1;
	i = -1;
	pthread_mutex_lock(&philo -> common -> n_times_mutex);
	while (finished && philo -> common -> n_eaten[++i] != -1)
		if (philo -> common -> n_eaten[i]
			< philo -> common -> n_times_to_eat)
			finished = 0;
	pthread_mutex_unlock(&philo -> common -> n_times_mutex);
	if (finished)
	{
		pthread_mutex_lock(&philo -> common -> die_mutex);
		philo -> common -> dead = YES;
		pthread_mutex_unlock(&philo -> common -> die_mutex);
	}
}

int	is_fork_free(t_philo *philo)
{
	pthread_mutex_lock(&philo -> common -> fork_mutex);
	if (*philo -> l_fork == FREE && philo -> r_fork == FREE
		&& !dead(philo))
	{
		return (1);
	}
	pthread_mutex_unlock(&philo -> common -> fork_mutex);
	return (0);
}

long int	get_time()
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
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
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
