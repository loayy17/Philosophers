/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:28:43 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/18 15:44:46 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_args(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	if (check_args(data) != 0)
		return (1);
	data->philo_pid = malloc(sizeof(int) * data->nb_philo);
	if (!data->philo_pid)
		return (1);
	return (0);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	if(data->death == SEM_FAILED)
	{
		free(data->philo_pid);
		free(data);
		return (1);
	}
	sem_post(data->death);
    sem_wait(data->death);
	sem_unlink("/meals");
	data->meals = sem_open("/meals", O_CREAT, 0644, 0);
	if (data->meals == SEM_FAILED)
	{
		free(data->philo_pid);
		free(data);
		return (1);
	}
	sem_post(data->meals);
	sem_wait(data->meals);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
	{
		free(data->philo_pid);
		free(data);
		return (1);
	}
	sem_post(data->forks);
	sem_wait(data->forks);
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	
	if (data->print == SEM_FAILED)
	{
		free(data->philo_pid);
		free(data);
		return (1);
	}
	sem_post(data->print);
	sem_wait(data->print);
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (init_args(argc, argv, data) != 0)
		return (1);
	if (init_semaphores(data) != 0)
		return (1);
	return (0);
}
