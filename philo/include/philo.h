/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:08:16 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/16 20:09:32 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long			start_time;
	int				dead_flag;
	pthread_mutex_t	meal_lock;
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
	MEAL,
	PHILOS
};
int					validate_args(int argc, char **argv);
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philosophers(t_data *data);
long				get_time(void);
void				precise_usleep(long milliseconds, t_data *data);
void				*monitor_routine(void *arg);
void				start_monitor(t_data *data);
void				*philo_routine(void *arg);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				print_message(t_philo *philo, int type, int force);
int					is_dead(t_data *data);
void				cleanup_resources(t_data *data);
void				free_data(t_data *data, int error);
void				free_forks(t_data *data, int n);
void				free_philos(t_data *data);
int					dead_lock_checker(t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
#endif