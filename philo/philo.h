#ifndef PHILO_H
# define PHILO_H
# define PARSE_ERR "Error arguments. Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef enum e_dead
{
	YES,
	NO
}	e_dead;

typedef enum e_fork
{
	FREE,
	USED
}	e_fork;

typedef struct s_philo
{
	int		id;
	e_dead		*dead;
	e_fork		*r_fork;
	e_fork		*l_fork;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

//parse.c
int	parse(int argc, char **argv);

//utils.c
int	ft_atoi(const char *str);

//start.c
void	*start();

#endif
