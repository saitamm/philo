/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:52:33 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/02 11:08:17 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alloc_init(t_data *data, t_argv nbr)
{
	data->philo = (t_philo *)malloc(nbr.nmbr_philo * sizeof(t_philo));
	data->forks = (t_mtx *)malloc(nbr.nmbr_philo * sizeof(t_mtx));
	data->tid = (pthread_t *)malloc(nbr.nmbr_philo * sizeof(pthread_t));
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
}

int	main(int ac, char **av)
{
	t_argv	nbr;
	t_data	data;

	if (ft_content(av, ac) == 1)
		exit(1);
	initial_nbr(av, &nbr, ac);
	alloc_init(&data, nbr);
	init_fork(&data, nbr);
	init_philo(&data, nbr);
	init_threads(&data, nbr);
	destory_all(&data);
	return (0);
}
