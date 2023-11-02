#include "../philo.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void	ph_eat(t_philo *philo)
{
	if (!dead(philo))
	{
	}
}

void	ph_sleep(t_philo *philo)
{
	long int	start_time;

	if (!dead(philo))
	{
		start_time = get_time();
		pthread_mutex_lock(&philo -> common -> write_mutex);
		printf("%ld %d is sleeping\n", get_time() - start_time, philo -> id);
		pthread_mutex_unlock(&philo -> common -> write_mutex);
		while (get_time() - start_time < philo -> common -> time_to_sleep)
		{
			check_death(philo);
			usleep(500);
		}
	}
}

void	ph_think(t_philo *philo)
{
	if (!dead(philo))
	{
	}
}

void	check_death(t_philo *philo)
{
	int	time_to_eat;
	long int	start_time;

	time_to_eat = philo -> common -> time_to_eat;
	start_time = philo -> common -> start_time;
	if (get_time() - start_time - philo -> ms_eaten > time_to_eat
		&& !dead(philo))
	{
		pthread_mutex_lock(&philo -> common -> die_mutex);
		philo -> common -> dead = YES;
		pthread_mutex_unlock(&philo -> common -> die_mutex);
		pthread_mutex_lock(&philo -> common -> write_mutex);
		printf("%ld %d died\n", get_time() - start_time, philo -> id);
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
