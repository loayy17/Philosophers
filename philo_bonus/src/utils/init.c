/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:28:43 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/23 21:10:51 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(t_data *data)
{
	if (data->n_philo < 1 || data->t_to_die < 0 || data->t_to_eat < 0
		|| data->t_to_sleep < 0 || (data->max_meals != -1
			&& data->max_meals < 1))
	{
		ft_print_error("Error: Invalid argument\n");
		return (1);
	}
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
	if (check_args(data) != 0)
		return (1);
	data->forks = NULL;
	data->n_philo_eat = NULL;
	data->death = NULL;
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
	{
		ft_print_error("Error: Failed to allocate memory for philosophers\n");
		return (1);
	}
	return (0);
}

int	init_semaphores(t_data *data)
{
	int	n_philo_eat;

	sem_unlink("/death_lock");
	sem_unlink("/forks_lock");
	sem_unlink("/n_philo_eat");
	sem_unlink("/print_lock");
	n_philo_eat = (data->n_philo / 2);
	if (data->n_philo & 1)
		n_philo_eat++;	
	data->n_philo_eat = sem_open("/n_philo_eat", O_CREAT | O_EXCL, 0644,
			n_philo_eat);
	data->death = sem_open("/death_lock", O_CREAT | O_EXCL, 0644, 1);
	data->forks = sem_open("/forks_lock", O_CREAT | O_EXCL, 0644, data->n_philo);
	data->print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0644, 1);	
	if (data->n_philo_eat == SEM_FAILED || data->death == SEM_FAILED
		|| data->forks == SEM_FAILED)
	{
		ft_print_error("Error: Failed to create semaphore\n");
		cleanup_simulation(data);
		return (1);
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
		data->philos[i].forks = data->forks;
		data->philos[i].death = data->death;
		data->philos[i].print_lock = data->print_lock;
		data->philos[i].n_philo_eat = data->n_philo_eat;
		data->philos[i].death_time = 0;
		data->philos[i].is_dead = 0;
	}
	return (0);
}
int	init_data(int argc, char **argv, t_data *data)
{
	if (init_args(argc, argv, data))
		return (1);
	if (init_semaphores(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
