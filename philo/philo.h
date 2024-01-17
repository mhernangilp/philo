/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:38:40 by mhernang          #+#    #+#             */
/*   Updated: 2024/01/17 13:38:43 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define PARSE_ERR "Error arguments. Usage: \
number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum t_dead
{
	YES,
	NO
}	t_dead;

typedef struct s_common
{
	t_dead			dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	long int		start_time;
	int				n_philo;
	int				*n_eaten;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	n_times_mutex;
	pthread_mutex_t	ms_mutex;
}	t_common;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				ms_eaten;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_common		*common;
}	t_philo;

//parse.c
int			parse(int argc, char **argv);

//initialize.c
t_philo		*initialize_philos(int n_philo, char **argv);

//start.c
void		*start(void *arg);

//activites.c
void		ph_eat(t_philo *philo);
void		ph_sleep(t_philo *philo);
void		ph_think(t_philo *philo);
int			dead(t_philo *philo);

//utils.c
int			check_full(t_philo *philos, int n_philos);
int			check_death(t_philo *philo);
long int	get_time(void);
int			ft_atoi(const char *str);

#endif
