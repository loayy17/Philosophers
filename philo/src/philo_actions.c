/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eat(t_philo *p)
{
	pthread_mutex_lock(&p->meal_lock);
	p->last_meal = get_time(0);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_lock);

	print_message(p, EAT);
	precise_usleep(p->t_eat, p);
}

static void grab_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		print_message(p, FORKS);
		pthread_mutex_lock(p->right_fork);
		print_message(p, FORKS);
	}
	else
	{
		precise_usleep(1, p);
		pthread_mutex_lock(p->right_fork);
		print_message(p, FORKS);
		pthread_mutex_lock(p->left_fork);
		print_message(p, FORKS);
	}
}

static void drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void *philo_routine(void *arg)
{
	t_philo *p = (t_philo *)arg;

	if (p->left_fork == p->right_fork)
	{
		pthread_mutex_lock(p->left_fork);
		print_message(p, FORKS);
		pthread_mutex_unlock(p->left_fork);
		precise_usleep(p->t_die, p);
		return (NULL);
	}
	if(p->id & 1)
		precise_usleep(1, p);
	while (1)
	{
		if(is_dead(p))
			break;
		grab_forks(p);
		eat(p);
		drop_forks(p);
		print_message(p, SLEEP);
		precise_usleep(p->t_sleep, p);
		print_message(p, THINK);
		if (is_dead(p))
			break;
	}
	return (NULL);
}
