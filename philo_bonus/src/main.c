/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:26:15 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/18 15:08:16 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_process(t_data *data)
{
	int	i;
	int	philo_broken;

	i = -1;
	philo_broken = 0;
	data->start_time = get_time_ms(0);
	while (++i < data->nb_philo)
	{
		data->philo_pid[i] = fork();
		if (data->philo_pid[i] == 0)
		{
			philo_broken = start_philosopher(i + 1, data);
		}
		if (philo_broken)
		{
			while (i >= 0)
			{
				kill(data->philo_pid[i], SIGKILL);
				i--;
			}
			break ;
		}
	}
}

int ft_print_error(char *str)
{
	while(*str)
	{
		write(2, str, 1);
		str++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pthread_t	monitors[2];
	t_data		data;

	if (validate_args(argc, argv))
		return (ft_print_error("Error: Invalid arguments\n"));
	if (init_data(argc, argv, &data))
	{
		free_data(&data);
		return (1);
	}
	start_process(&data);
	pthread_create(&monitors[1], NULL, &monitor_meals, &data);
	pthread_create(&monitors[0], NULL, &monitor_death, &data);
	pthread_join(monitors[1], NULL);
	pthread_join(monitors[0], NULL);
	cleanup_simulation(&data);
	return (0);
}
