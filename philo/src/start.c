#include "../philo.h"

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Hola soy el thread %d\n", philo -> id);
	return (NULL);
}
