/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:18 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/03 18:41:26 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_philosopher(t_data *data, int i)
{
	long	current_time;

	sem_wait(data->death_lock);
	current_time = get_time();
	printf("%ld %d\n", current_time, data->philo[i].id);
	printf("%ld %d\n", data->philo[i].last_meal, data->philo[i].id);
	printf("%d %d\n", data->t_die, data->philo[i].id);
	printf("%d %d\n", data->dead_flag, data->philo[i].id);
	
	if ((current_time - data->philo[i].last_meal) > data->t_die)
	{
		print_message(&data->philo[i], "died", "red", 1);
		data->dead_flag = 1;
		free_philos(data);
		sem_post(data->death_lock);
		return (1);
	}
	sem_post(data->death_lock);
	return (0);
}
static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_must_eat == -1)
		return (0);
	all_ate = 1;
	i = -1;
	sem_wait(data->death_lock);
	while (++i < data->n_philos)
	{
		if (data->philo[i].meals_eaten < data->n_must_eat)
		{
			all_ate = 0;
			break ;
		}
	}
	if (all_ate)
		data->dead_flag = 1;
	sem_post(data->death_lock);
	return (all_ate);
}

void	monitor_loop(t_data *data)
{
	int	i;
	int	stop;

	stop = 0;
	while (!stop)
	{
		i = -1;
		while (++i < data->n_philos)
		{
			if (check_philosopher(data, i))
			{
				stop = 1;
				break ;
			}
		}
		if (!stop && check_meals(data))
			stop = 1;
		usleep(100);
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	monitor_loop(data);
	return (NULL);
}

void	start_monitor(t_data *data)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		monitor_routine(data);
		cleanup_resources(data);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
}