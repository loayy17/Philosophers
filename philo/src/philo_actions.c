/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 05:36:19 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 05:36:20 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time(0);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_message(philo, EAT);
	precise_usleep(philo->t_eat, philo);
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
		print_message(philo, FORKS);
		if (*philo->dead_flag)
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, FORKS);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, FORKS);
		if (*philo->dead_flag)
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, FORKS);
	}
	return (0);
}

int	checker_dead_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->dead_flag)
	{
		pthread_mutex_unlock(philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, FORKS);
		pthread_mutex_unlock(philo->left_fork);
		precise_usleep(philo->t_die, philo);
		return (NULL);
	}
	while (!checker_dead_lock(philo))
	{
		if (grab_forks(philo))
			break ;
		eat(philo);
		drop_forks(philo->left_fork, philo->right_fork);
		print_message(philo, SLEEP);
		precise_usleep(philo->t_sleep, philo);
		print_message(philo, THINK);
	}
	return (NULL);
}