#ifndef PHILO_H
# define PHILO_H
# define PARSE_ERR "Error arguments. Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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

typedef struct s_common
{
	e_dead		dead;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_times_to_eat;
	int		*n_eaten;
	long int	start_time;
	int		n_philo;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	n_times_mutex;
}	t_common;

typedef struct s_philo
{
	int		id;
	pthread_t	thread;
	int		ms_eaten;
	e_fork		l_fork;
	e_fork		*r_fork;
	t_common	*common;
}	t_philo;

//parse.c
int		parse(int argc, char **argv);

//initialize.c
t_philo		*initialize_philos(int n_philo, char **argv);

//start.c
void		*start(void *arg);

//activites.c
void	ph_eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_think(t_philo *philo, int start);
void	check_death(t_philo *philo);
int	dead(t_philo *philo);

//utils.c
void		check_full(t_philo *philo);
int		is_fork_free(t_philo *philo);
long int	get_time();
int		ft_atoi(const char *str);

#endif
