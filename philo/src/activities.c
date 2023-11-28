#include "../philo.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static int	dead_wm(t_philo *philo);

void	ph_eat(t_philo *philo)
{
	long int	start_time;
	long int	eat_st_time;

	eat_st_time = get_time();
	start_time = philo -> common -> start_time;
	pthread_mutex_lock(&philo -> common -> write_mutex);
	printf("%ld %d has taken a fork\n", get_time() - start_time,
		philo -> id);
	philo -> r_fork = USED;
	*philo -> l_fork = USED;
	printf("%ld %d is eating\n", get_time() - start_time,
		philo -> id);
	pthread_mutex_unlock(&philo -> common -> write_mutex);
	pthread_mutex_unlock(&philo -> common -> fork_mutex);
	philo -> ms_eaten = get_time() - start_time;
	if (philo -> common -> n_times_to_eat != -1)
	{
		pthread_mutex_lock(&philo -> common -> n_times_mutex);
		philo -> common -> n_eaten[philo -> id - 1] += 1;
		pthread_mutex_unlock(&philo -> common -> n_times_mutex);
		check_full(philo);
	}
	while (get_time() - eat_st_time < philo -> common
		-> time_to_eat && !dead(philo))
	{
		check_death(philo);
		usleep(500);
	}
	pthread_mutex_lock(&philo -> common -> fork_mutex);
	philo -> r_fork = FREE;
	*philo -> l_fork = FREE;
	pthread_mutex_unlock(&philo -> common -> fork_mutex);
}

void	ph_sleep(t_philo *philo)
{
	long int	start_time;
	long int	sleep_st_time;

	sleep_st_time = get_time();
	start_time = philo -> common -> start_time;
	pthread_mutex_lock(&philo -> common -> write_mutex);
	printf("%ld %d is sleeping\n", get_time() - start_time, philo -> id);
	pthread_mutex_unlock(&philo -> common -> write_mutex);
	while (get_time() - sleep_st_time < philo -> common
		-> time_to_sleep && !dead(philo))
	{
		check_death(philo);
		usleep(500);
	}
}

void	ph_think(t_philo *philo)
{
	long int	start_time;

	start_time = philo -> common -> start_time;
	pthread_mutex_lock(&philo -> common -> write_mutex);
	printf("%ld %d is thinking\n", get_time() - start_time, philo -> id);
	pthread_mutex_unlock(&philo -> common -> write_mutex);
	while (!is_fork_free(philo) && !dead(philo))
	{
		check_death(philo);
		usleep(500);
	}
}

void	check_death(t_philo *philo)
{
	int		time_to_die;
	long int	start_time;

	time_to_die = philo -> common -> time_to_die;
	start_time = philo -> common -> start_time;
	pthread_mutex_lock(&philo -> common -> die_mutex);
	if (get_time() - start_time - philo -> ms_eaten > time_to_die
		&& !dead_wm(philo))
	{
		pthread_mutex_lock(&philo -> common -> write_mutex);
		philo -> common -> dead = YES;
		printf("%ld %d died\n", get_time() - start_time, philo -> id);
		pthread_mutex_unlock(&philo -> common -> write_mutex);
	}
	pthread_mutex_unlock(&philo -> common -> die_mutex);
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

static int	dead_wm(t_philo *philo)
{
	if (philo -> common -> dead == NO)
	{
		pthread_mutex_unlock(&philo -> common -> die_mutex);
		return (0);
	}
	return (1);
}
