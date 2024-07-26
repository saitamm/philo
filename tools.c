/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:55:05 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/26 11:05:05 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;
	size_t			milliseconds;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf("gettimeofday Error");
		return (-1);
	}
	milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (milliseconds);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;
	pthread_mutex_lock(philo->write_mutex);
	time = get_time() - philo->start_time;
	if (check_dead(philo))
	{

		printf("%zu %d is died soumaya\n", time, philo->id);
		philo->flag = 1;
		pthread_mutex_unlock(philo->write_mutex);
		philo->nbr_finished++;
		return ;
	}
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

void	destory_all(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	while (i < data->philo[0].nmbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
