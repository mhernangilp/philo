/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:43 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/30 16:49:34 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo -> id % 2 == 0 || (philo -> common -> n_philo % 2 == 1
		&& philo -> id == 1))
	{
		usleep(500);
		ph_think(philo, 1);
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
			ph_think(philo, 0);
	}
	return (NULL);
}
