/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:09:49 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/11 10:33:47 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nmbr)
	{
		if (get_time() - philo[i].last_meal >= philo[i].data->time_to_die
			&& philo[i].flag_eating == 1)
		{
			print_message(DEAD, philo);
			pthread_mutex_lock(&philo[0].data->dead_mutex);
			philo[i].flag = 1;
			philo[i].data->dead_flag = 1;
			pthread_mutex_unlock(&philo[0].data->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nmbr)
	{
		pthread_mutex_lock(&philo[0].data->meal_mutex);
		if (philo[i].count_meal >= philo[i].nmbr_meal)
			philo[0].nbr_finished++;
		pthread_mutex_unlock(&philo[0].data->meal_mutex);
		i++;
	}
	if (philo->nbr_finished == philo->nmbr)
	{
		pthread_mutex_lock(&philo[0].data->dead_mutex);
		philo->data->dead_flag  = 1;
		pthread_mutex_unlock(&philo[0].data->dead_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (1)
	{
		if (philosophers_dead(data) == 1 || data->data->dead_flag == 1 || all_eat(data) == 1)
			break ;
	}
	return (data);
}
