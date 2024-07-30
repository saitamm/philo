/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:09:49 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/27 12:21:20 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nmbr)
	{
		if (get_time() - philo[i].last_meal >= philo[i].data->time_to_eat
			&& philo[i].flag_eating == 1)
		{
			print_message("died", philo);
			pthread_mutex_lock(philo[0].dead_mutex);
			philo[i].flag = 1;
			pthread_mutex_unlock(philo[0].dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_eat(t_philo *philo)
{
	if (philo->count_meal == philo->nmbr_meal && philo->nmbr_meal != -1)
		return (1);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*philo;

	philo = (t_data *)arg;
	while (1)
	{
		if (philosophers_dead(philo->philo) == 1 || philo->dead_flag == 1)
			break ;
	}
	return (philo);
}
