/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:27:08 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 02:59:39 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *philo)
{
	sem_wait(philo->death);
	if (get_time_ms(philo->last_meal) > philo->t_to_die)
	{
		philo->last_meal = get_time_ms(philo->start_time);
		sem_post(philo->death);
		return (1);
	}
	sem_post(philo->death);
	return (philo->max_meals == 0);
}

int	start_philosopher(t_philo *philo, t_data *data)
{
	int	exit_status;

	philo->pid = getpid();
	if (data->n_philo == 1)
	{
		print_message(FORK, philo);
		precise_usleep(data->t_to_die, philo);
	}
	while (data->n_philo > 1)
	{
		if (check_dead(philo) || eat(philo) || sleep_philo(philo) || think(philo))
			break ;
	}
	if(philo->max_meals == 0)
		exit_status = 0;
	else
		exit_status = philo->id;
	clean_child_data(philo, data);
	exit(exit_status);
}

int	grap_forks(t_philo *philo)
{
	if (check_dead(philo))
		return (-1);
	sem_wait(philo->n_philo_eat);
	if (check_dead(philo))
		return (-1);
	sem_wait(philo->forks);
	philo->n_forks--;
	if(philo->n_forks == 1)
		{
		if(precise_usleep(philo->t_to_die, philo))
			return (-1);
		}
	if (print_message(FORK, philo) || check_dead(philo))
	return (-1);
	philo->n_forks--;
	sem_wait(philo->forks);
	if (print_message(FORK, philo) || check_dead(philo))
		return (-1);
	return (0);
}

int	throw_forks(t_philo *philo)
{
	sem_post(philo->forks);
	philo->n_forks++;
	sem_post(philo->forks);
	philo->n_forks++;
	sem_post(philo->n_philo_eat);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->max_meals == 0)
		return (-1);
	if (grap_forks(philo) || print_message(EAT, philo))
		return (philo->id);
	philo->last_meal = get_time_ms(0);
	if (precise_usleep(philo->t_to_eat, philo))
		return (philo->id);
	philo->max_meals--;
	if (throw_forks(philo))
		return (philo->id);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_message(SLEEP, philo))
		return (1);
	precise_usleep(philo->t_to_sleep, philo);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_message(THINK, philo))
		return (1);

	return (0);
}
