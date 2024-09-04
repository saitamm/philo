/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:36:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/04 14:03:00 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo[0].data->dead_mutex);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo[0].data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[0].data->dead_mutex);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	take_fork(&first_fork, &second_fork, philo);
	pthread_mutex_lock(first_fork);
	print_message("has taken a fork", philo);
	if (!check_one_philo(philo))
		return (pthread_mutex_unlock(first_fork), 1);
	pthread_mutex_lock(second_fork);
	print_message("has taken a fork", philo);
	philo->flag_eating = 1;
	pthread_mutex_lock(&philo->data->meal_mutex);
	print_message("is eating", philo);
	pthread_mutex_lock(&philo->data->time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->time_mutex);
	philo->count_meal++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
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
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (eat(philo))
			break ;
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (philo->data->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
