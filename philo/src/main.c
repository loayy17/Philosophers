/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 05:36:13 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 05:36:13 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher(t_data *data, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->meal_lock);
	current_time = get_time(data->philos[i].last_meal);
	pthread_mutex_unlock(&data->meal_lock);
	if (current_time > data->t_die)
	{
		pthread_mutex_lock(&data->death_lock);
		data->dead_flag = 1;
		printf(RED "%-6ld %d died\n" RESET, get_time(data->start_time),
			data->philos[i].id);
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_must_eat == -1)
		return (0);
	all_ate = 1;
	pthread_mutex_lock(&data->meal_lock);
	i = -1;
	while (++i < data->n_philos)
	{
		if (data->philos[i].meals_eaten < data->n_must_eat)
		{
			all_ate = 0;
			break ;
		}
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (all_ate);
}
int	monitor_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_lock);
		if (check_philosopher(data, i))
			return (1);
	}
	return (0);
}

int	start_monitor(t_data *data)
{
	while (1)
	{
		if (monitor_death(data))
			return (1);
		if (check_meals(data))
		{
			pthread_mutex_lock(&data->death_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		usleep(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	if (start_monitor(&data))
	{
		cleanup_resources(&data);
		return (1);
	}
	cleanup_resources(&data);
	return (0);
}