/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:44:23 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/12 21:39:56 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher(t_data *data, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->death_lock);
	current_time = get_time();
	if ((current_time - data->philo[i].last_meal) > data->t_die)
	{
		print_message(&data->philo[i], DEAD, 1);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_must_eat == -1)
		return (0);
	i = -1;
	pthread_mutex_lock(&data->death_lock);
	while (++i < data->n_philos)
	{
		all_ate = 1;
		if (data->philo[i].meals_eaten < data->n_must_eat)
		{
			all_ate = 0;
			break;
		}
	}
	if (all_ate)
		data->dead_flag = 1;
	pthread_mutex_unlock(&data->death_lock);
	return (all_ate);
}

static void	monitor_loop(t_data *data)
{
	int	i;
	int	stop;

	stop = 0;
	while (!stop)
	{
		i = -1;
		while (++i < data->n_philos)
		{
			if (check_philosopher(data, i))
			{
				stop = 1;
				break ;
			}
		}
		if (!stop && check_meals(data))
			stop = 1;
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	monitor_loop(data);
	return (NULL);
}

void	start_monitor(t_data *data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return ;
	pthread_join(monitor, NULL);
}
