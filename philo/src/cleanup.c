/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:46:21 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/16 20:14:36 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_data *data)
{
	int	i;

	i = data->n_philos;
	while (--i >= 0)
	{
		pthread_join(data->philo[i].thread, NULL);
	}
	free(data->philo);
	data->philo = NULL;
}

void	free_forks(t_data *data, int n)
{
	int	i;

	if (n <= 0)
		return ;
	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	data->forks = NULL;
}

void	free_data(t_data *data, int error)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->n_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
	}
	if (error >= PRINT)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->death_lock);
	}
	if (error == PHILOS && data->philo)
	{
		i = -1;
		while (++i < data->n_philos)
		{
			pthread_detach(data->philo[i].thread);
		}
		free(data->philo);
		data->philo = NULL;
	}
}

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

void	cleanup_resources(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philo[i].thread, NULL);
	destroy_mutexes(data);
	free(data->forks);
	free(data->philo);
}
