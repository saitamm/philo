/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:28:07 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/07 16:42:21 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_not_digit(char c)
{
	if (!(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_check(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_is_not_digit(av[i]))
			return (1);
		i++;
	}
	return (0);
}

void	error_input(char *str)
{
	write(2, str, ft_strlen(str));
}

int	ft_content(char **av, int ac)
{
	if (ac != 5 && ac != 6)
		return (error_input(WR_NB), 1);
	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) <= 0
		|| ft_check(av[1]) == 1)
		return (error_input(IN_PN), 1);
	if (ft_atoi(av[2]) <= 0 || ft_check(av[2]) == 1)
		return (error_input(TIME_DIE), 1);
	if (ft_atoi(av[3]) <= 0 || ft_check(av[3]) == 1)
		return (error_input(TIME_EAT), 1);
	if (ft_atoi(av[4]) <= 0 || ft_check(av[4]) == 1)
		return (error_input(TIME_SLEEP), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5]) == 1))
		return (error_input(MEAL), 1);
	return (0);
}
