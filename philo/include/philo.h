#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORKS 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long			start_time;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*meal_lock;
	int				*dead_flag;
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long			start_time;
	int				dead_flag;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

// Function declarations
int					validate_args(int argc, char **argv);
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philosophers(t_data *data);
long				get_time(long time);
void				precise_usleep(long milliseconds, t_philo *philo);
void				*monitor_routine(void *arg);
int					start_monitor(t_data *data);
void				*philo_routine(void *arg);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				print_message(t_philo *philo, int type);
int					is_dead(t_philo *philo);
void				cleanup_resources(t_data *data);
void				free_data(t_data *data);
void				destroy_mutexes(t_data *data);
void				print_colored(int id, int type, t_philo *philo);
int					is_dead(t_philo *philo);
int					checker_dead_lock(t_philo *philo);
void 				ft_print_error(char *str);
#endif