/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 05:36:05 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 05:36:06 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->n_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

void	cleanup_resources(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].thread, NULL);
	destroy_mutexes(data);
	if (data->philos)
		free(data->philos);
}