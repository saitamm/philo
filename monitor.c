/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:09:49 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/26 12:07:36 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_philo)
	{
		if (get_time() - philo[i].last_meal >= philo[i].time_to_eat
			&& philo[i].flag_eating == 1)
		{
			print_message("died 8*******************", philo);
			pthread_mutex_lock(philo[0].dead_mutex);
			philo[i].flag = 1;
			pthread_mutex_unlock(philo[0].dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int all_eat(t_philo *philo)
{
    if (philo->count_meal == philo->nmbr_meal && philo->nmbr_meal != -1)
        return(1);
    return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philosophers_dead(philo) == 1 || philo->flag == 1 || philo->nbr_finished >= philo->nmbr || all_eat(philo) == 1)
			return (philo);
	}
	return (philo);
}
