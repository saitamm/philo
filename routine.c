/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:36:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/25 13:09:24 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	int	t;

	t = philo->flag;
	pthread_mutex_lock(philo->dead_mutex);
	if (t == 1)
	{
		print_message("died%%%%%%%%%%%%%%%%%", philo);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);

	if (philo->nmbr == 1)
	{
		print_message("died", philo);
        philo->nbr_finished++;
		philo->flag = 1;
        return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->eat_mutex);
	print_message("is eating", philo);
	philo->flag_eating = 1;
	philo->count_meal++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eat_mutex);
	philo->flag_eating = 0;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	ft_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	while (check_dead(philo))
		sleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
 
	while (check_dead(philo) != 1)
	{
		eat(philo);
		think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
