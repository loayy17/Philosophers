/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:27:08 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/24 21:28:08 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *philo)
{
	sem_wait(philo->death);
	if (get_time_ms(philo->last_meal) > philo->t_to_die)
	{
		philo->last_meal = get_time_ms(philo->start_time);
		philo->is_dead = 1;
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
		print_message(philo, FORK, BLUE, "🍴");
		precise_usleep(data->t_to_die, philo);
	}
	while (data->n_philo > 1)
	{
		if(check_dead(philo))
			break ;
		if(eat(philo))
			break ;
		if (sleep_philo(philo))
			break ;
		if (think(philo))
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
	if (print_message(philo , FORK, MAGENTA,"🍴"))
		return (-1);
	if(check_dead(philo))
		return (-1);
	sem_wait(philo->forks);
	if (print_message(philo, FORK, MAGENTA,"🍴"))
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
	if (philo->max_meals == 0)
		return (-1);
	if (grap_forks(philo))
		return (philo->id);
	if(print_message(philo, EAT, GREEN, "🍝"))
		return (philo->id);	
	philo->last_meal = get_time_ms(0);
	philo->max_meals--;
	if (precise_usleep(philo->t_to_eat, philo))
		return (philo->id);
	if (throw_forks(philo))
		return (philo->id);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_message( philo,SLEEP, YELLOW, "🛌"))
		return (1);
	if(precise_usleep(philo->t_to_sleep, philo))
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_message( philo,THINK, MAGENTA, "🤔"))
		return (1);

	return (0);
}
