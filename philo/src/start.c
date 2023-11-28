#include "../philo.h"
#include <stddef.h>
#include <unistd.h>

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo -> id % 2 == 0 || (philo -> common -> n_philo % 2 == 1
		&& philo -> id == 1))
	{
		usleep(500);
		ph_think(philo);
	}
	while (!dead(philo)) // && !he terminado de comer
	{
		//como
		if (!dead(philo))
			ph_eat(philo);
		//duermo
		if (!dead(philo))
			ph_sleep(philo);
		//pienso
		if (!dead(philo))
			ph_think(philo);
	}
	return (NULL);
}
