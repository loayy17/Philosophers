/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:12:26 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/15 20:49:39 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 1
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
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		*philo_pid;
	long	start_time;
	sem_t	*forks;
	sem_t	*s7n;
	sem_t	*death;
	sem_t	*meals;
	sem_t	*print;
}			t_data;

typedef struct s_philo
{
	int		id;
	int		meals;
	long	last_meal;
	sem_t	*last_meal_sem;
}			t_philo;

typedef struct s_monitor
{
	int		id;
	long	time_to_die;
	long	start_time;
	long	*last_meal;
	sem_t	*last_meal_sem;
	sem_t	*death;
	sem_t	*print;

}			t_monitor;

int			validate_args(int argc, char **argv);
int			init_data(int argc, char **argv, t_data *data);
int			start_philosopher(int id, t_data *data);
long		get_time_ms(long start_time);
void		print_message(int id, int type, long start_time, sem_t *print);
void		start_monitor_thread(t_philo *philo, t_data *data);
void		cleanup_simulation(t_data *data);
void		precise_usleep(long ms);
int			ft_atoi(const char *str);
t_philo		*create_philo(int id);
int			check_args(t_data *data);
void		*monitor_death(void *arg);
void		*monitor_meals(void *arg);
void		eat(t_data *data, int id);
void		update_last_meal(t_philo *philo, long start);
void		kill_children(t_data *data);
void		free_data(t_data *data);

#endif
