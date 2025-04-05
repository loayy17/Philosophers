/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:32:01 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/05 14:14:55 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_MEALS "/meals"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
	long				start_time;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*meals;
	int					dead;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meals;
	long				last_meal;
	pthread_t			dead;
	pid_t				pid;
	t_data				*data;
}						t_philo;

// Validation
int						validate_args(int argc, char **argv);
int						ft_atoi(const char *str);

// Init
int						init_data(t_data *data, int argc, char **argv);
int						init_semaphores(t_data *data, int *ret);
void					cleanup(t_data *data);

// Time
long					get_time(void);
void					precise_sleep(long ms);

// Philosopher
void					philo_life(t_philo *philo);
int						start_simulation(t_data *data, int *ret);

// Utils
void					print_status(t_philo *philo, char *msg, int color,
							char *emoji);
int						check_args(t_data *data, int *ret);
void					free_philos(t_data *data);
void					free_close(t_data *data);
void					error_message(int ret);
void					grap_forks(t_data *data);
void					throw_forks(t_philo *philo);	
int						eat(t_philo *philo);
#endif