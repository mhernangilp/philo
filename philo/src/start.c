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
	if (philo -> id % 2 == 0)
		usleep(500);
	while (!dead(philo))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
