/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:27 by lalhindi          #+#    #+#             */
/*   Updated: 2025/03/30 00:24:22 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

int	grap_fork(t_philo *philo)
{
	sem_wait(philo->left_fork);
	sem_wait(philo->right_fork);
	return (0);
}

int	throw_fork(t_philo *philo)
{
	sem_post(philo->left_fork);
	sem_post(philo->right_fork);
	return (0);
}

void	eat(t_philo *philo)
{
	print_message(philo, "is eating", "green", 0);
	// usleep(philo->data->t_eat * 1000);
	philo->meals_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		sem_wait(philo->left_fork);
		print_message(philo, "has taken a fork", "blue", 0);
		sem_post(philo->left_fork);
		if (is_dead(philo->data))
			usleep(philo->data->t_die * 1000);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		if (grap_fork(philo))
			break ;
		eat(philo);
		throw_fork(philo);
		print_message(philo, "is sleeping", "yellow", 0);
		precise_usleep(philo->data->t_sleep, philo->data);
		print_message(philo, "is thinking", "magenta", 0);
	}
    return (NULL);
}