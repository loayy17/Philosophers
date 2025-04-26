/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:18:10 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:18:10 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem_initial(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/n_philo_eat");
	sem_unlink("/death");
	sem_unlink("/print");
	data->forks = NULL;
	data->n_philo_eat = NULL;
	data->death = NULL;
	data->print_lock = NULL;
}

void	safe_sem_close(sem_t **sem)
{
	if (*sem != NULL && *sem != SEM_FAILED)
	{
		sem_close(*sem);
		*sem = NULL;
	}
}

void	cleanup_partial_init(t_data *data)
{
	safe_sem_close(&data->forks);
	safe_sem_close(&data->n_philo_eat);
	safe_sem_close(&data->death);
	safe_sem_close(&data->print_lock);
}

void	clean_child_data(t_philo *philo, t_data *data)
{
	safe_sem_close(&philo->forks);
	safe_sem_close(&philo->n_philo_eat);
	safe_sem_close(&philo->death);
	safe_sem_close(&philo->print_lock);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

void	cleanup_simulation(t_data *data)
{
	safe_sem_close(&data->forks);
	safe_sem_close(&data->n_philo_eat);
	safe_sem_close(&data->death);
	safe_sem_close(&data->print_lock);
	sem_unlink("/forks");
	sem_unlink("/n_philo_eat");
	sem_unlink("/death");
	sem_unlink("/print");
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
