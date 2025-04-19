/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:26:05 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/19 20:40:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_children(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		kill(data->philos[j].pid, SIGKILL);
	}
}
void	clean_child_data(t_philo *philo, t_data *data)
{
	if (philo->forks != SEM_FAILED)
		sem_close(philo->forks);
	if (philo->n_philo_eat != SEM_FAILED)
		sem_close(philo->n_philo_eat);
	if (philo->death != SEM_FAILED)
		sem_close(philo->death);
	if (data->philos)
		free(data->philos);
}
void	cleanup_simulation(t_data *data)
{
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->n_philo_eat != SEM_FAILED)
		sem_close(data->n_philo_eat);
	if (data->death != SEM_FAILED)
		sem_close(data->death);
	sem_unlink("/forks");
	sem_unlink("/n_philo_eat");
	sem_unlink("/death");
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
