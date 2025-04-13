/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:44:09 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/13 21:54:21 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo->last_meal = get_time();
	print_message(philo, FORKS, 0);
	print_message(philo, FORKS, 0);
	print_message(philo, EAT, 0);
	if (dead_lock_checker(data))
		return ;
	philo->meals_eaten++;
	precise_usleep(data->t_eat, data);
}

static void	drop_forks(pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
}

static int	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo->data))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo->data))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, FORKS, 0);
		pthread_mutex_unlock(philo->left_fork);
		if (is_dead(philo->data))
			precise_usleep(philo->data->t_die, philo->data);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		if (grab_forks(philo))
			break ;
		eat(philo);
		drop_forks(philo->left_fork, philo->right_fork);
		print_message(philo, SLEEP, 0);
		precise_usleep(philo->data->t_sleep, philo->data);
		print_message(philo, THINK, 0);
	}
	return (NULL);
}
