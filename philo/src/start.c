#include "../philo.h"
#include <stddef.h>

void	*start(void *arg)
{
	t_philo	*philo;
	struct timeval	tiempo;
	size_t		resta;

	philo = (t_philo *)arg;
	printf("Hola soy el thread %d\n", philo -> id);
	while (philo -> common -> dead == NO) // && !he terminado de comer
	{
		//como
		gettimeofday(&tiempo, NULL);
		resta = tiempo.tv_sec * 1000 + tiempo.tv_usec - philo ->common -> start_time;
		printf("%ld %d has taken a fork\n", resta, philo -> id);
		gettimeofday(&tiempo, NULL);
		resta = tiempo.tv_sec * 1000 + tiempo.tv_usec - philo ->common -> start_time;
		printf("%ld %d is eating\n", resta, philo -> id);
		//duermo
		gettimeofday(&tiempo, NULL);
		resta = tiempo.tv_sec * 1000 + tiempo.tv_usec - philo ->common -> start_time;
		printf("%ld %d is sleeping\n", resta, philo -> id);
		////mientras duermo miro si me muero
		//pienso
		gettimeofday(&tiempo, NULL);
		resta = tiempo.tv_sec * 1000 + tiempo.tv_usec - philo ->common -> start_time;
		printf("%ld %d is thinking\n", resta, philo -> id);
		////mientas pienso miro si me muero
	}
	return (NULL);
}
