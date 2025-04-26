/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:05:04 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:05:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(t_data *data)
{
	if (data->n_philo < 1 || data->t_to_die < 0 || data->t_to_eat < 0
		|| data->t_to_sleep < 0 || (data->max_meals != -1
			&& data->max_meals < 1))
		return (ft_print_error("Error: Invalid argument\n"));
	return (0);
}

int	init_args(int argc, char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	if (check_args(data))
		return (2);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (ft_print_error("Error: Philosophers malloc failed\n"));
	return (0);
}

int	init_semaphores(t_data *data)
{
	init_sem_initial(data);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
		return (ft_print_error("Error: Forks semaphore creation failed\n"));
	data->n_philo_eat = sem_open("/n_philo_eat", O_CREAT, 0644, (data->n_philo
				+ 1) / 2);
	if (data->n_philo_eat == SEM_FAILED)
	{
		cleanup_partial_init(data);
		return (ft_print_error(
				"Error: n_philo_eat semaphore creation failed\n"));
	}
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	if (data->death == SEM_FAILED)
	{
		cleanup_partial_init(data);
		return (ft_print_error("Error: Death semaphore creation failed\n"));
	}
	data->print_lock = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED)
	{
		cleanup_partial_init(data);
		return (ft_print_error("Error: Print lock semaphore creation failed\n"));
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].max_meals = data->max_meals;
		data->philos[i].t_to_die = data->t_to_die;
		data->philos[i].t_to_eat = data->t_to_eat;
		data->philos[i].t_to_sleep = data->t_to_sleep;
		data->philos[i].start_time = get_time_ms(0);
		data->philos[i].last_meal = get_time_ms(0);
		data->philos[i].is_dead = 0;
		data->philos[i].pid = 0;
		data->philos[i].forks = data->forks;
		data->philos[i].n_philo_eat = data->n_philo_eat;
		data->philos[i].death = data->death;
		data->philos[i].print_lock = data->print_lock;
	}
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	return_value;

	return_value = init_args(argc, argv, data);
	if (return_value == 1)
	{
		free(data->philos);
		return (1);
	}
	else if (return_value == 2)
	{
		return (1);
	}
	if (init_semaphores(data))
	{
		cleanup_simulation(data);
		return (1);
	}
	if (init_philos(data))
		return (1);
	return (0);
}
