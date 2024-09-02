/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:55:05 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/02 17:04:21 by sait-amm         ###   ########.fr       */
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

int	check_one_philo(t_philo *philo)
{
	if (philo->nmbr == 1)
	{
		print_message(DEAD, philo);
		return (0);
	}
	return (1);
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

	pthread_mutex_lock(&philo->data->time_mutex);
	time = get_time() - philo->start_time;
	pthread_mutex_unlock(&philo->data->time_mutex);
	pthread_mutex_lock(&philo->data->write_mutex);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	destory_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	while (i < data->philo[0].nmbr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data->tid);
}
