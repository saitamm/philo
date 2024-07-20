/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:52:33 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/20 10:33:37 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac , char **av)
{
	t_argv		nbr;
	t_philo		philo[MAX_PHILO];
	t_mtx		fork[MAX_PHILO];
	t_table		t;
	
	if (ft_content(av, ac) == 1)
		exit(1);
	initial_nbr(av, &nbr, ac);
	init_table(&t, nbr, philo);
	init_fork(fork, nbr);
	init_philo(fork, philo, nbr, &t);
}