/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:28:07 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/20 10:16:06 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int ft_is_not_digit(char c)
{
    if (!(c >= '0' && c <= '9'))
        return (1);
    return (0);
}

int   ft_check(char *av)
{
    int i;
    
    i = 1;
    while (av[i])
    {
        if (ft_is_not_digit(av[i]))
            return (1);
        i++;
    }

    return (0);
}

int	ft_content(char **av, int ac)
{
    if (ac != 5 && ac != 6)
		return (write(2, "wrong of argument number\n", 26), 1);
	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) <= 0
		|| ft_check(av[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(av[2]) <= 0 || ft_check(av[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || ft_check(av[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || ft_check(av[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
    return (0);
}