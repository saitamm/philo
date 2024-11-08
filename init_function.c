/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:43:11 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/03 14:40:23 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_data *data, t_argv nbr)
{
	int	i;

	i = 0;
	while (i < nbr.nmbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nbr.nmbr_philo)
	{
		data->philo[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philo[i].r_fork = &data->forks[nbr.nmbr_philo - 1];
		else
			data->philo[i].r_fork = &data->forks[i - 1];
		i++;
	}
}

void	initial_nbr(char **av, t_argv *nbr, int ac)
{
	nbr->nmbr_philo = ft_atoi(av[1]);
	nbr->time_to_die = ft_atoi(av[2]);
	nbr->time_to_eat = ft_atoi(av[3]);
	nbr->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		nbr->nbr = 2147483647;
	else
		nbr->nbr = ft_atoi(av[5]);
}

void	init_philo(t_data *data, t_argv nbr)
{
	int	i;

	i = 0;
	while (i < nbr.nmbr_philo)
	{
		data->time_to_die = nbr.time_to_die;
		data->time_to_eat = nbr.time_to_eat;
		data->time_to_sleep = nbr.time_to_sleep;
		data->philo[i].id = i + 1;
		data->philo[i].count_meal = 0;
		data->philo[i].start_time = get_time();
		data->philo[i].last_meal = get_time();
		data->philo[i].flag_eating = 0;
		data->philo[i].flag = 0;
		data->philo[i].nbr_finished = 0;
		data->philo[i].nmbr = nbr.nmbr_philo;
		data->philo[i].nmbr_meal = nbr.nbr;
		data->philo[i].data = data;
		i++;
	}
}

void	init_threads(t_data *data, t_argv nbr)
{
	int			i;
	pthread_t	monit;

	i = -1;
	if (pthread_create(&monit, NULL, &monitor, data->philo) != 0)
		destroy_all("Error in creation", data->forks, data);
	while (++i < nbr.nmbr_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]) != 0)
			destroy_all("Error in creation", data->forks, data);
	}
	if (pthread_join(monit, NULL) != 0)
		destroy_all("Error in join", data->forks, data);
	i = 0;
	while (i < nbr.nmbr_philo)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			destroy_all("Error in join", data->forks, data);
		i++;
	}
}
