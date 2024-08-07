/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:43:11 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/07 16:53:29 by sait-amm         ###   ########.fr       */
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
		nbr->nbr = -1;
	else
		nbr->nbr = ft_atoi(av[5]);
}

void	init_philo(t_data *data, t_argv nbr)
{
	int	i;

	i = 0;
	while (i < nbr.nmbr_philo)
	{
		data->philo[i].id = i + 1;
		data->time_to_die = nbr.time_to_die;
		data->time_to_eat = nbr.time_to_eat;
		data->time_to_sleep = nbr.time_to_sleep;
		data->philo[i].count_meal = 0;
		data->philo[i].start_time = get_time();
		data->philo[i].last_meal = get_time();
		data->philo[i].flag_eating = 0;
		data->philo[i].flag = 0;
		data->philo[i].nbr_finished = 0;
		data->philo[i].eat_mutex = &data->eat_mutex;
		data->philo[i].dead_mutex = &data->dead_mutex;
		data->philo[i].write_mutex = &data->write_mutex;
		data->philo[i].nmbr = nbr.nmbr_philo;
		data->philo[i].nmbr_meal = nbr.nbr;
		data->philo[i].data = data;
		i++;
	}
}

void	error(t_data *data, char *str, int i)
{
	printf("%s\n", str);
	free(data->forks);
	free(data->tid);
	while (i > 0)
	{
		free(data->philo);
		i--;
	}
}

void	init_threads(t_data *data, t_argv nbr)
{
	int			i;
	pthread_t	monit;

	i = -1;
	if (pthread_create(&monit, NULL, &monitor, data) != 0)
	{
		write(2, "error mssg", 11);
		return ;
	}
	while (++i < nbr.nmbr_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]) != 0)
			error(data, "Error in creation of threads", i);
	}
	if (pthread_join(monit, NULL) != 0)
	{
		write(2, "error mssg", 11);
		return ;
	}
	while (i < nbr.nmbr_philo)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			error(data, "errr in join of threads", i);
		i++;
	}
}
