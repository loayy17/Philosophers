/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:04:44 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/05 09:04:53 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_args(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	data->dead = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	return (0);
}

int	init_semaphores(t_data *data, int *ret)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEALS);
	data->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, data->n_philos);
	data->print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	data->meals = sem_open(SEM_MEALS, O_CREAT, S_IRWXU, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->meals == SEM_FAILED)
	{
		*ret = 3;
		return (1);
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (init_args(data, argc, argv) || check_args(data, &ret))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
	{
		ret = 6;
		return (ret);
	}
	if (!ret && init_semaphores(data, &ret))
		return (ret);
	init_philo(data);
	return (ret);
}
