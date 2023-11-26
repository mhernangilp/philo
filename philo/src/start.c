#include "../philo.h"
#include <stddef.h>
#include <unistd.h>

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo -> id % 2 == 0)
	{
		usleep(500);
		ph_think(philo);
	}
	while (!dead(philo)) // && !he terminado de comer
	{
		//como
		ph_eat(philo);
		//duermo
		ph_sleep(philo);
		//pienso
		ph_think(philo);
	}
	return (NULL);
}
