/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:27 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/03 18:33:38 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grap_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	return (0);
}

int	throw_fork(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

static void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->death_lock);
	if (data->dead_flag)
	{
		sem_post(data->death_lock);
		return ;
	}
	philo->last_meal = get_time();
	philo->meals_eaten++;
	sem_post(data->death_lock);
	print_message(philo, "has taken a fork", "blue", 0);
	print_message(philo, "has taken a fork", "blue", 0);
	print_message(philo, "is eating", "green", 0);
	precise_usleep(data->t_eat, data);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		sem_wait(philo->data->forks);
		print_message(philo, "has taken a fork", "blue", 0);
		sem_post(philo->data->forks);
		if (is_dead(philo->data))
			precise_usleep(philo->data->t_die, philo->data);
		free_data(philo->data, PHILOS);	
		exit(0);
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