/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:09:49 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/03 10:59:13 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_mtx **first, t_mtx **second, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
	else
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
}

int	philosophers_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nmbr)
	{
		pthread_mutex_lock(&philo[0].data->time_mutex);
		if (get_time() - philo[i].last_meal >= philo[i].data->time_to_die
			&& philo[i].flag_eating == 0)
		{
			pthread_mutex_unlock(&philo[0].data->time_mutex);
			print_message(DEAD, philo);
			pthread_mutex_lock(&philo[0].data->dead_mutex);
			philo[0].data->dead_flag = 1;
			pthread_mutex_unlock(&philo[0].data->dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[0].data->time_mutex);
		i++;
	}
	return (0);
}

int	all_eat(t_philo *philo)
{
	int	i;
	int	finiched;

	i = 0;
	finiched = 0;
	while (i < philo[0].nmbr)
	{
		pthread_mutex_lock(&philo[0].data->meal_mutex);
		if (philo[i].count_meal >= philo[i].nmbr_meal)
			finiched++;
		pthread_mutex_unlock(&philo[0].data->meal_mutex);
		i++;
	}
	if (finiched == philo->nmbr)
	{
		pthread_mutex_lock(&philo[0].data->dead_mutex);
		(*philo).data->dead_flag = 1;
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
		if (philosophers_dead(data) == 1 || all_eat(data) == 1)
			break ;
	}
	return (data);
}
