/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:02:47 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/03 18:41:17 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int				n_philos;
	int				t_eat;
	int				t_think;
	int				t_sleep;
	int				n_must_eat;
	long			start_time;
	int				dead_flag;
	int				t_die;
	sem_t			*forks;
	sem_t			*print_lock;
	sem_t			*death_lock;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals_eaten;
	pthread_t		thread;
	t_data			*data;
	long			last_meal;
}					t_philo;

enum				e_mutex
{
	NONE,
	FORK,
	PRINT,
	DEATH,
	PHILOS
};

int					validate_args(int argc, char **argv);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					init_data(t_data *data, int argc, char **argv);
int					init_philosophers(t_data *data);
long				get_time(void);
int					init_semaphore(t_data *data);
void				start_monitor(t_data *data);
void				cleanup_resources(t_data *data);
int					is_dead(t_data *data);
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
void				precise_usleep(long milliseconds, t_data *data);
void				print_message(t_philo *philo, char *msg, char *color,
						int force);
void				free_data(t_data *data, int error);
void				free_philos(t_data *data);
#endif