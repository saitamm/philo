#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define MAX_PHILO 200

typedef pthread_mutex_t t_mtx;

typedef struct e_argv
{
	int nmbr_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nbr;
}t_argv;


typedef struct s_philo
{
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		count_meal;
	size_t	start_time;
	size_t	last_meal;
	int 	flag;
	t_mtx	*r_fork;
	t_mtx	*l_fork;
	t_mtx	*deal_mutex;
	t_mtx	*eat_mutex;
	t_mtx	*write_mutex;
	pthread_t	*t;
	int		nmbr;
	int		id;
}t_philo;

typedef struct e_table
{
	int	flag;
	t_mtx	deal_mutex;
	t_mtx	eat_mutex;
	t_mtx	write_mutex;
	t_philo	*philo;
	
}t_table;

//parting function 

int		ft_atoi(const char	*c);
int		ft_is_not_digit(char str);
int		ft_check(char *av);
int	ft_content(char **av, int ac);

// initial function

void    initial_nbr(char **av, t_argv *nbr, int ac);
void	init_fork(t_mtx *fork, t_argv nbr);
void	init_table(t_table *t, t_philo *philo);
void	init_philo(t_mtx *fork, t_philo *philo, t_argv nbr, t_table *t);

// Routine

void	*routine(void *arg);
int check_dead(t_philo *philo);
void    print_message(char *str, t_philo *philo);
void    eat(t_philo *philo);
size_t get_time(void);
void    think(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    *routine(void *arg);
void	init_threads(t_philo *philo, t_argv nbr);
#endif