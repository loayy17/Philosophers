/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:38:45 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:38:45 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *p)
{
	pthread_mutex_lock(&p->meal_lock);
	p->last_meal = get_time(0);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_lock);
	if (print_message(p, EAT, GREEN, "🍝"))
		return (1);
	precise_usleep(p->t_eat, p);
	if (is_dead(p))
		return (1);
	return (0);
}

static void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static int	grab_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		if (even_philo(p))
			return (1);
	}
	else
	{
		precise_usleep(1, p);
		pthread_mutex_lock(p->right_fork);
		if (print_message(p, FORK, BLUE, "🍴"))
		{
			pthread_mutex_unlock(p->right_fork);
			return (1);
		}
		pthread_mutex_lock(p->left_fork);
		if (print_message(p, FORK, BLUE, "🍴"))
		{
			drop_forks(p);
			return (1);
		}
	}
	return (0);
}

int	handle_single_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (print_message(p, FORK, BLUE, "🍴"))
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_unlock(p->left_fork);
	precise_usleep(p->t_die, p);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if ((p->left_fork == p->right_fork) && handle_single_philo(p))
		return (NULL);
	if (p->id % 2)
		precise_usleep(1, p);
	while (1)
	{
		if (is_dead(p) || grab_forks(p))
			break ;
		if (eat(p))
		{
			drop_forks(p);
			break ;
		}
		drop_forks(p);
		if (print_message(p, SLEEP, YELLOW, "😴"))
			break ;
		precise_usleep(p->t_sleep, p);
		if (print_message(p, THINK, MAGENTA, "🤔") || is_dead(p))
			break ;
	}
	return (NULL);
}
