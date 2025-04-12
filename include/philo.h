#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long			start_time;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

enum				e_mutex
{
	NONE,
	FORK,
	PRINT,
	DEATH,
	PHILOS
};

// Main
int					validate_args(int argc, char **argv);

// Init
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philosophers(t_data *data);

// Time
long				get_time(void);
void				precise_usleep(long milliseconds, t_data *data);

// Monitor
void				*monitor_routine(void *arg);
void				start_monitor(t_data *data);

// Actions
void				*philo_routine(void *arg);

// Utils
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				print_message(t_philo *philo, char *msg, char *color,
						int force);
int					is_dead(t_data *data);

// Cleanup
void				cleanup_resources(t_data *data);
void				free_data(t_data *data, int error);
void				free_forks(t_data *data, int n);
void				free_philos(t_data *data);
int					dead_lock_checker(t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
#endif