/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_resources(t_data *d)
{
	int i;
	for (i = 0; i < d->n_philos; i++)
		pthread_join(d->philos[i].thread, NULL);
	for (i = 0; i < d->n_philos; i++)
	{
		pthread_mutex_destroy(&d->philos[i].meal_lock);
		pthread_mutex_destroy(&d->philos[i].dead_lock);
	}
	free(d->philos);
	for (i = 0; i < d->n_philos; i++)
		pthread_mutex_destroy(&d->forks[i]);
	free(d->forks);
	pthread_mutex_destroy(&d->print_lock);
}
