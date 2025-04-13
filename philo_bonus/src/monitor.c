/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:26:39 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/12 21:03:18 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_monitor	*mon_philo;
	long		now;
	int			dead;

	mon_philo = (t_monitor *)arg;
	dead = 0;
	while (!dead)
	{
		now = get_time_ms(mon_philo->start_time);
		sem_wait(mon_philo->last_meal_sem);
		if (now - *mon_philo->last_meal > mon_philo->time_to_die)
			dead = 1;
		sem_post(mon_philo->last_meal_sem);
	}
	print_message(mon_philo->id, DEAD, mon_philo->start_time, mon_philo->print);
	sem_post(mon_philo->death);
	free(mon_philo);
	return (NULL);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	sem_wait(data->death);
	while (++i < data->nb_philo)
		sem_post(data->meals);
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i++ < data->nb_philo)
		sem_wait(data->meals);
	sem_post(data->death);
	return (NULL);
}

void	start_monitor_thread(t_philo *philo, t_data *data)
{
	t_monitor	*mon_philo;
	pthread_t	thread;

	mon_philo = malloc(sizeof(t_monitor));
	if (!mon_philo)
		return ;
	mon_philo->id = philo->id;
	mon_philo->time_to_die = data->time_to_die;
	mon_philo->start_time = data->start_time;
	mon_philo->last_meal = &philo->last_meal;
	mon_philo->last_meal_sem = philo->last_meal_sem;
	mon_philo->death = data->death;
	mon_philo->print = data->print;
	pthread_create(&thread, NULL, &monitor_routine, mon_philo);
}
