/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:36:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/07 15:46:17 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->nmbr)
	{
		if (philo->data->philo[i].flag == 1)
			return (1);
		i++;
	}
	return (0);
}
int	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	pthread_mutex_lock(first_fork);
	print_message("has taken a fork", philo);
	if (philo->nmbr == 1)
	{
		print_message(DEAD, philo);
		pthread_mutex_unlock(first_fork);
		philo->nbr_finished++;
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->flag = 1;
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->eat_mutex);
	print_message("is eating", philo);
	philo->flag_eating = 1;
	philo->count_meal++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->data->time_to_eat);
	philo->flag_eating = 0;
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	return (0);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	ft_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	// while (check_dead(philo))
	// 	sleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (eat(philo) ||philo->data->dead_flag == 1)
			break ;
		think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
