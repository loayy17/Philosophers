/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 05:35:29 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 05:35:31 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_must_eat = -1;
	if (argc == 6)
		data->n_must_eat = ft_atoi(argv[5]);
}

int	check_args(t_data *data, int argc)
{
	if (data->n_philos < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->n_must_eat < 1))
		return (1);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (1);
	for (i = 0; i < data->n_philos; i++)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (free(data->forks), 1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->death_lock, NULL) != 0
		|| pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		free(data->forks);
		destroy_mutexes(data);
		return (1);
	}
	return (0);
}

void	init_philo_data(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].n_philos = data->n_philos;
	data->philos[i].t_die = data->t_die;
	data->philos[i].t_eat = data->t_eat;
	data->philos[i].t_sleep = data->t_sleep;
	data->philos[i].last_meal = data->start_time;
	data->philos[i].start_time = data->start_time;
	data->philos[i].meals_eaten = 0;
	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
	data->philos[i].print_lock = &data->print_lock;
	data->philos[i].death_lock = &data->death_lock;
	data->philos[i].meal_lock = &data->meal_lock;
	data->philos[i].dead_flag = &data->dead_flag;
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->n_philos)
	{
		init_philo_data(data, i);
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (free(data->philos), 1);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	init_args(data, argc, argv);
	data->start_time = get_time(0);
	data->dead_flag = 0;
	if (check_args(data, argc))
		return (1);
	if (init_mutexes(data))
		return (1);
	if (init_philosophers(data))
		return (destroy_mutexes(data), 1);
	return (0);
}