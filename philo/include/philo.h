/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
/* actions for printing */
enum e_action { DEAD, FORKS, EAT, SLEEP, THINK };

/* philosopher struct holds exactly what each thread needs */
typedef struct s_philo
{
	int             id;
	int             meals_eaten;
	long            last_meal;
	long            start_time;
	long            t_die;
	long            t_eat;
	long            t_sleep;
	long death_time;
	int             dead_flag;
	pthread_t       thread;
	pthread_mutex_t meal_lock;
	pthread_mutex_t dead_lock;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *print_lock;
}               t_philo;

/* shared data */
typedef struct s_data
{
	int             n_philos;
	int             n_must_eat;
	long            t_die;
	long            t_eat;
	long            t_sleep;
	long            start_time;
	t_philo         *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t  print_lock;
}               t_data;

int     validate_args(int argc, char **argv);
int     init_data(t_data *data, int argc, char **argv);
void    cleanup_resources(t_data *data);

long    get_time(long start);
void    precise_usleep(long ms, t_philo *philo);

int     is_dead(t_philo *philo);
void    print_message(t_philo *philo, int action);

void   *philo_routine(void *arg);
void ft_print_error(char *str);

#endif
