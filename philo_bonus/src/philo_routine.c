/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:27:08 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/19 21:08:13 by lalhindi         ###   ########.fr       */
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
	return (0);
}

void	free_philo(t_philo *philo, t_data *data)
{
	(void)data;
	if (philo->forks != SEM_FAILED)
		sem_close(philo->forks);
	if (philo->n_philo_eat != SEM_FAILED)
		sem_close(philo->n_philo_eat);
	if (philo->death != SEM_FAILED)
		sem_close(philo->death);
	free(data->philos);
}

int	start_philosopher(int id, t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[id - 1];
	philo->pid = getpid();
	if (data->n_philo == 1)
	{
		if (print_message(FORK, philo))
			return (philo->id);
		precise_usleep(data->t_to_die, philo);
		sem_post(data->forks);
		clean_child_data(philo, data);
		exit(philo->id);
	}
	while (1)
	{
		if (check_dead(philo))
			break ;
		if (eat(philo))
			break ;
		if (data->max_meals && sleep_philo(philo))
			break ;
		if (data->max_meals && think(philo))
			break ;
	}
	id = philo->id;
	clean_child_data(philo, data);
	if (philo->max_meals == 0)
		exit(0);
	else
		exit(id);
}

int	grap_forks(t_philo *philo)
{
	sem_wait(philo->n_philo_eat);
	sem_wait(philo->forks);
	if (print_message(FORK, philo))
		return (-1);
	if (check_dead(philo))
		return (-1);
	sem_wait(philo->forks);
	if (print_message(FORK, philo))
		return (-1);
	if (check_dead(philo))
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
	if (print_message(EAT, philo))
		return (philo->id);
	philo->last_meal = get_time_ms(0);
	if (precise_usleep(philo->t_to_eat, philo))
		return (philo->id);
	philo->max_meals--;
	if(throw_forks(philo))
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