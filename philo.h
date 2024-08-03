#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define MAX_PHILO 200

#define WR_NB "wrong of argument number\n"
#define IN_PN "Invalid philosophers number\n"
#define TIME_DIE "Invalid time to die\n"
#define TIME_EAT "Invalid time to eat\n"
#define TIME_SLEEP "Invalid time to sleep\n"
#define MEAL "Invalid number of times each philosopher must eat\n"
#define DEAD "died"
typedef pthread_mutex_t	t_mtx;

struct s_data;

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
	int flag_eating;    // if thread was eating flag_eating = 1;
	int count_meal;     // every time thread will eat count_meal will crement
	size_t start_time;  // time the thread will start ear
	size_t last_meal;   // last time thread was eat a meal
	t_mtx *r_fork;      // right fork of philo
	t_mtx *l_fork;      // left fork of philo
	t_mtx *dead_mutex;  // mutex of dead
	t_mtx *eat_mutex;   // mutex of eat
	t_mtx *write_mutex; // mutex of write
	pthread_t t;        // thread
	int nmbr;           // number f philo input
	int id;             // id f philo start in 1
	int					nbr_finished;
	int					flag;
	int					nmbr_meal;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					dead_flag;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	t_mtx				dead_mutex;
	t_mtx				eat_mutex;
	t_mtx				write_mutex;
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
void					destory_all(t_data *data);
size_t					ft_strlen(char *str);

#endif