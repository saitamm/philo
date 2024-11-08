/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:14:59 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/11 09:57:49 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\n'
		|| c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *c)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_whitespace(c[i]) == 1)
		i++;
	if (c[i] == '+' || c[i] == '-')
	{
		if (c[i] == '-')
			sign = (-1) * sign;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		result = result * 10 + c[i] - '0';
		i++;
	}
	return (result * sign);
}
