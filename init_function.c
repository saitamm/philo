/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:43:11 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/22 15:06:23 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *t, t_philo *philo)
{
	t->flag = 0;
	t->philo = philo;
	pthread_mutex_init(&t->deal_mutex, NULL);
	pthread_mutex_init(&t->eat_mutex, NULL);
	pthread_mutex_init(&t->write_mutex, NULL);
}

void	init_fork(t_mtx *fork, t_argv nbr)
{
	int	i;

	i = 0;
	while (i < nbr.nmbr_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void    initial_nbr(char **av, t_argv *nbr, int ac)
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

void	init_philo(t_mtx *fork, t_philo *philo, t_argv nbr, t_table *t)
{
	int	i;

	i = 0;
	while (i < nbr.nmbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = nbr.time_to_die;
		philo[i].time_to_eat = nbr.time_to_eat;
		philo[i].time_to_sleep = nbr.time_to_sleep;
		philo[i].count_meal = 0;
		philo[i].start_time = get_time();
		philo[i].flag = 0;
		philo[i].eat_mutex = &t->eat_mutex;
		philo[i].deal_mutex = &t->deal_mutex;
		philo[i].write_mutex = &t->write_mutex;
		philo[i].l_fork = &fork[i];
		philo[i].nmbr = nbr.nmbr_philo;
		if (i == 0)
			philo[i].r_fork = &fork[0];
		else
			philo[i].r_fork = &fork[i-1]; 
		i++;
	}
}

void	init_threads(t_philo *philo, t_argv nbr)
{
	int	i;

	i = 0;
	while(i < nbr.nmbr_philo)
	{
		if (pthread_create(philo[i].t, NULL, routine, NULL) !=0)
			printf("::::::::::::::::::\n");
		i++;
	}
	i = 0;
	while (i < nbr.nmbr_philo)
	{
		if (pthread_join(philo[i].t, NULL) != 0)
			printf("*******************\n");
		i++;
	}
}