/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:26:15 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 03:32:01 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->n_philo_eat != SEM_FAILED)
		sem_close(data->n_philo_eat);
	if (data->death != SEM_FAILED)
		sem_close(data->death);
	if (data->philos)
		free(data->philos);
}

void	wait_children(t_data *data)
{
	int		i;
	int		status;
	int		id;
	int		meals_completed;

	i = -1;
	meals_completed = 0;
	while (++i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		id = (((status)&0xff00) >> 8);
		if (id != 0)
		{
			sem_wait(data->death);
			
			data->philos[id - 1].death_time = get_time_ms(data->philos[id - 1].start_time);
			kill_children(data, data->n_philo);
			break ;
		}
		else
		{
			meals_completed++;
			if (meals_completed == data->n_philo)
			{
				kill_children(data, i);
				return ;
			}
		}
	}
	printf(RED "| %-6ld | %d | is dead        | 💀 | \n" RESET, data->philos[id - 1].death_time,id);
}

int	start_process(t_data *data)
{
	int	i;
	int	philo_broken;

	i = -1;
	philo_broken = 0;
	while (++i < data->n_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
		{
			kill_children(data, i);
			ft_print_error("Error: Failed to create process\n");
			return (1);
		}
		if (data->philos[i].pid == 0)
		{
			philo_broken = start_philosopher(&data->philos[i], data);
		}
		if (philo_broken)
		{
			kill_children(data, i);
			ft_print_error("Error: Failed to start philosopher\n");
			return (1);
		}
	}
	wait_children(data);
	return (0);
}

int	ft_print_error(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
	{
		free_data(&data);
		return (1);
	}
	if (start_process(&data))
	{
		free_data(&data);
		return (1);
	}
	cleanup_simulation(&data);
	return (0);
}
