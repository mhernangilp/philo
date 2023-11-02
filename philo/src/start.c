#include "../philo.h"
#include <stddef.h>

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
