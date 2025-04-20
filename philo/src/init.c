/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:44:34 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/16 20:09:42 by lalhindi         ###   ########.fr       */
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
	{
		data->n_must_eat = ft_atoi(argv[5]);
	}
}

int	check_args(t_data *data, int argc)
{
	if (data->n_philos < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->n_must_eat < 1))
	{
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
	{
		return (FORK);
	}
	i = 0;
	while (i < data->n_philos && ret == 0)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			ret = FORK;
		}
		i++;
	}
	if (ret == 0 && pthread_mutex_init(&data->print_lock, NULL))
	{
		ret = FORK;
	}
	if (ret == 0 && pthread_mutex_init(&data->death_lock, NULL))
	{
		ret = DEATH;
	}
	if (pthread_mutex_init(&data->meal_lock, NULL))
	{
		ret = MEAL;
	}
	if (ret != 0)
	{
		cleanup_mutexes(data, ret, i);
	}
	return (ret);
}

void	cleanup_mutexes(t_data *data, int ret, int i)
{
	if (ret == DEATH)
	{
		free_forks(data, data->n_philos);
	}
	else
	{
		free_forks(data, i);
	}
	if (ret == DEATH)
	{
		pthread_mutex_destroy(&data->print_lock);
	}
}

int	init_philosophers(t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
	{
		return (PHILOS);
	}
	i = 0;
	while (i < data->n_philos && ret == 0)
	{
		initialize_philosopher(data, i);
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]))
		{
			ret = PHILOS;
		}
		i++;
	}
	if (ret != 0)
	{
		free_philos(data);
	}
	return (ret);
}

void	initialize_philosopher(t_data *data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].last_meal = data->start_time;
	data->philo[i].meals_eaten = 0;
	data->philo[i].data = data;
	data->philo[i].left_fork = &data->forks[i];
	data->philo[i].right_fork = &data->forks[(i + 1) % data->n_philos];
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	ret;

	ret = 0;
	init_args(data, argc, argv);
	data->start_time = get_time();
	data->dead_flag = 0;
	if (check_args(data, argc))
	{
		return (1);
	}
	ret = init_mutexes(data);
	if (ret == 0)
	{
		ret = init_philosophers(data);
	}
	if (ret)
	{
		free_data(data, ret);
	}
	return (ret != 0);
}
