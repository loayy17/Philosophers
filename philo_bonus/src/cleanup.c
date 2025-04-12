/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:26:05 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/12 19:26:33 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_data(t_data *data)
{
	if (data->philo_pid)
		free(data->philo_pid);
	if (data)
		free(data);
}

void	kill_children(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		kill(data->philo_pid[i], SIGKILL);
}

void	cleanup_simulation(t_data *data)
{
	kill_children(data);
	free(data->philo_pid);
	sem_close(data->death);
	sem_close(data->meals);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->s7n);
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("meals");
	sem_unlink("print");
	free(data);
}
