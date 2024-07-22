/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:36:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/07/22 15:02:51 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_dead(t_philo *philo)
{
    int t = philo->flag;
    pthread_mutex_lock(philo->deal_mutex);
    if (t == 1)
    {
        print_message("died", philo);
        return (1);
    }
    pthread_mutex_unlock(philo->deal_mutex);
    return (0);
}

void    print_message(char *str, t_philo *philo)
{
    size_t  time;

    pthread_mutex_lock(philo->write_mutex);
    time = get_time() - philo->start_time;
    if (!check_dead(philo))
    {
        printf("%zu %d is died\n", time, philo->id);
        return;
    }
    printf("%zu %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(philo->write_mutex);
}
void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_message("has taken a fork", philo);
    if (philo->nmbr == 1)
    {
        print_message("died", philo);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);    
    print_message("has taken a fork", philo);
    print_message("is eating", philo);
    pthread_mutex_lock(philo->eat_mutex);
    philo->count_meal++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(philo->eat_mutex);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void    think(t_philo *philo)
{
    print_message("is thinking", philo);
}

void    ft_sleep(t_philo *philo)
{ 
    print_message("is sleeping", philo);
    while (check_dead(philo))   
        sleep(500);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo*)arg;
    free(arg);

    while (1) 
	{
		eat(philo);
		think(philo);
		ft_sleep(philo);
    }
    return (NULL);
}




// // void    routine(void *arg)
// // {
// //     t_thread    *philo;

// //     philo = (t_thread *) arg;
// //     while (philo->flag)
// //     {
// //         eat(philo->t, philo->time_to_die);
        
// //     }
// // }