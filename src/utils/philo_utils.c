/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:40:32 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/11 22:43:59 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->death_lock);
	ret = data->dead_flag;
	pthread_mutex_unlock(&data->death_lock);
	return (ret);
}

int	dead_lock_checker(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

int	all_meals_completed(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_must_eat == -1)
		return (0);
	all_ate = 1;
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->philo[i].meals_eaten < data->n_must_eat)
			all_ate = 0;
		pthread_mutex_unlock(&data->death_lock);
		if (!all_ate)
			break ;
	}
	return (all_ate);
}
