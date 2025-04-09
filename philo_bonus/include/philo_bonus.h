#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
// # include <semaphore.h>
// # include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "forks"
# define SEM_PRINT "print"
# define SEM_MEALS "meals"
# define SEM_DEATH "death"
# define SEM_FORK_MUTEX "fork_mutex"
# define SEM_MEAL_SEM "meal_sem"
# define NULL ((void *)0)
// typedef struct s_philo	t_philo;

// typedef struct s_data
// {
// 	int					n_philos;
// 	int					t_die;
// 	int					t_eat;
// 	int					t_sleep;
// 	int					must_eat;
// 	int					death;
// 	long				start_time;
// 	sem_t				*forks;
// 	sem_t				*print;
// 	sem_t				*death_lock;
// 	t_philo				*philos;
// }						t_data;
typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	last_meal;
	sem_t	*meal;
}			t_philo;

typedef struct s_monitor_philo
{
	int		id;
	long	t_die;
	long	*start_time;
	long	*last_meal;
	sem_t	*meal;
	sem_t	*death;
	sem_t	*print;
}			t_monitor_philo;

typedef struct s_data
{
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		max_meals;
	int		death;
	long	start_time;
	sem_t	*forks;
	sem_t	*death_sem;
	sem_t	*meals;
	sem_t	*fork_mutex;
	sem_t	*print;
	pid_t	*pids;
}			t_data;

int			print_stderr(char *str, int ret);
long		get_time(long from);
t_philo		*init_philo(int id);
int			init_data(t_data *data, int argc, char **argv);
int			init_semaphores(t_data *data);
int			check_args(t_data *data);
int			validate_args(int argc, char **argv);
void		precise_sleep(long time);
void		print_action(t_data *data, int id, char *msg);
void		start_processes(t_data *data);
void		cleanup(t_data *data);
int			ft_atoi(const char *str);
int			check_args(t_data *data);

#endif