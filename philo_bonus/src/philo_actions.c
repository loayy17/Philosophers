/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:10:43 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:10:43 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grap_forks(t_philo *philo)
{
	sem_wait(philo->n_philo_eat);
	sem_wait(philo->forks);
	if (print_message(philo, FORK, MAGENTA, "🍴"))
		return (-1);
	sem_wait(philo->forks);
	if (print_message(philo, FORK, MAGENTA, "🍴"))
		return (-1);
	return (0);
}

int	throw_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->n_philo_eat);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->max_meals == 0 || is_dead(philo))
		return (-1);
	if (grap_forks(philo))
		return (-1);
	if (print_message(philo, EAT, GREEN, "🍝"))
		return (-1);
	sem_wait(philo->death);
	philo->last_meal = get_time_ms(0);
	if (philo->max_meals > 0)
		philo->max_meals--;
	sem_post(philo->death);
	if (precise_usleep(philo->t_to_eat, philo))
		return (-1);
	if (throw_forks(philo))
		return (-1);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_message(philo, SLEEP, YELLOW, "🛌"))
		return (-1);
	if (precise_usleep(philo->t_to_sleep, philo))
		return (-1);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_message(philo, THINK, MAGENTA, "🤔"))
		return (-1);
	if (precise_usleep(1, philo))
		return (-1);
	return (0);
}
