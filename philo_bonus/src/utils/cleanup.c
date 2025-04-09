/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:03:12 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/09 22:55:55 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_message(int error_code)
{
	if (error_code == 1)
		printf("Error: Wrong number of arguments\n");
	else if (error_code == 2)
		printf("Error: Invalid arguments\n");
	else if (error_code == 3)
		printf("Error: Failed to create semaphore\n");
	else if (error_code == 4)
		printf("Error: Failed to create process\n");
	else if (error_code == 5)
		printf("Error: Failed to join process\n");
	else if (error_code == 6)
		printf("Error: Failed to allocate memory\n");
	else
		printf("Unknown error occurred\n");
}

void	free_philos(t_data *data)
{
	if (data->pids)
	{
		free(data->pids);
	}
}

void	kill_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (data->philos[i].pid != 0)
			kill(data->philos[i].pid, SIGKILL);
	}
}

void	cleanup(t_data *data)
{
	int	i;
	int	result;

	i = -1;
	while (++i < data->n_philos)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
		{
			kill_philosophers(data);
			break ;
		}
	}
	free_close(data);
}
