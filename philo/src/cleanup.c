/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:40:50 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:40:50 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_len(const char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		i++;
		len++;
	}
	if (len >= 10)
		return (-2);
	return (0);
}

void	cleanup_resources(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
		pthread_join(d->philos[i].thread, NULL);
	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_destroy(&d->philos[i].meal_lock);
		pthread_mutex_destroy(&d->philos[i].dead_lock);
	}
	free(d->philos);
	i = -1;
	while (++i < d->n_philos)
		pthread_mutex_destroy(&d->forks[i]);
	free(d->forks);
	pthread_mutex_destroy(&d->print_lock);
}
