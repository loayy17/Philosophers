/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:27:08 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/18 15:08:22 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_philosopher(int id, t_data *data)
{
	t_philo	*philo;

	philo = create_philo(id);
	if (!philo)
		return (id);
	start_monitor_thread(philo, data);
	if (data->nb_philo == 1)
	{
		sem_wait(data->forks);
		print_message(id, FORK, data->start_time, data->print);
		precise_usleep(data->time_to_die);
		sem_post(data->forks);
		return (0);
	}
	while (1)
	{
		eat(data, id, philo, data->start_time);
		if (philo->meals == data->max_meals && data->max_meals != -1)
		{
			sem_close(philo->last_meal_sem);
			sem_unlink("/last_meal_sem");
			sem_post(data->meals);
			
		}
		print_message(id, SLEEP, data->start_time, data->print);
		precise_usleep(data->time_to_sleep);
		print_message(id, THINK, data->start_time, data->print);
	}
	return (0);
}

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals = 0;
	philo->last_meal = 0;
	sem_unlink("/last_meal_sem");
	philo->last_meal_sem = sem_open("/last_meal_sem", O_CREAT, 0644, 1);
	if (philo->last_meal_sem == SEM_FAILED)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	eat(t_data *data, int id, t_philo *philo, long start)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	print_message(id, FORK, data->start_time, data->print);
	print_message(id, FORK, data->start_time, data->print);
	print_message(id, EAT, data->start_time, data->print);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_ms(start);
	sem_post(philo->last_meal_sem);
	philo->meals++;
	precise_usleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

