/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:12:26 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/23 20:46:36 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "is dead"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int		id;
	pid_t	pid;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		max_meals;
	long	start_time;
	long	death_time;
	long	last_meal;
	int		is_dead;
	sem_t	*forks;
	sem_t	*n_philo_eat;
	sem_t	*death;
	sem_t	*print_lock;
}			t_philo;

typedef struct s_data
{
	int		n_philo;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		max_meals;
	int		is_dead;
	long	death_time;
	sem_t	*n_philo_eat;
	sem_t	*forks;
	sem_t	*death;
	sem_t	*print_lock;
	t_philo	*philos;
}			t_data;

void		kill_children(t_data *data, int i);
void		clean_child_data(t_philo *philo, t_data *data);
void		cleanup_simulation(t_data *data);
long		get_time_ms(long start);
int    print_message(t_philo *philo, char *status, char *color, char *emoji);
int			precise_usleep(long time_wait, t_philo *philo);
int			eat(t_philo *philo);
int			sleep_philo(t_philo *philo);
int			think(t_philo *philo);
int			ft_atoi(const char *str);
int			check_args(t_data *data);
int			ft_print_error(char *str);
int			check_dead(t_philo *philo);
int			start_philosopher(t_philo *philo, t_data *data);
int			validate_args(int argc, char **argv);
int			init_data(int argc, char **argv, t_data *data);
#endif
