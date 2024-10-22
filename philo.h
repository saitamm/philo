/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:44:45 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/03 14:32:33 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define MAX_PHILO 200

# define WR_NB "wrong of argument number\n"
# define IN_PN "Invalid philosophers number\n"
# define TIME_DIE "Invalid time to die\n"
# define TIME_EAT "Invalid time to eat\n"
# define TIME_SLEEP "Invalid time to sleep\n"
# define MEAL "Invalid number of times each philosopher must eat\n"
# define DEAD "died"

typedef pthread_mutex_t	t_mtx;

struct					s_data;

typedef struct e_argv
{
	int					nmbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr;
}						t_argv;

typedef struct s_philo
{
	int					flag_eating;
	int					count_meal;
	size_t				start_time;
	size_t				last_meal;
	t_mtx				*r_fork;
	t_mtx				*l_fork;
	pthread_t			t;
	int					nmbr;
	int					id;
	int					flag;
	int					nmbr_meal;
	int					nbr_finished;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					dead_flag;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	t_mtx				dead_mutex;
	t_mtx				write_mutex;
	t_mtx				time_mutex;
	t_mtx				meal_mutex;
	t_philo				*philo;
	t_mtx				*forks;
	pthread_t			*tid;

}						t_data;

// parting function

int						ft_atoi(const char *c);
int						ft_is_not_digit(char str);
int						ft_check(char *av);
int						ft_content(char **av, int ac);

// initial function

void					init_threads(t_data *data, t_argv nbr);
void					init_philo(t_data *data, t_argv nbr);
void					initial_nbr(char **av, t_argv *nbr, int ac);
void					init_fork(t_data *data, t_argv nbr);
void					alloc_init(t_data *data, t_argv nbr);
void					init_threads(t_data *data, t_argv nbr);

// routine and actions

int						eat(t_philo *philo);
void					think(t_philo *philo);
void					*routine(void *arg);
void					ft_sleep(t_philo *philo);

// monitor

void					*monitor(void *arg);

// threads

int						check_dead(t_philo *philo);
int						philosophers_dead(t_philo *philo);

// help unctions

size_t					get_time(void);
void					print_message(char *str, t_philo *philo);
int						ft_usleep(size_t milliseconds);
void					destroy_all(char *str, t_mtx *forks, t_data *data);
size_t					ft_strlen(char *str);
int						check_one_philo(t_philo *philo);
void					take_fork(t_mtx **first, t_mtx **second,
							t_philo *philo);

#endif