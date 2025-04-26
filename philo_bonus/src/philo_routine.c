/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:11:16 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:11:16 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	int	flag;

	sem_wait(philo->death);
	flag = philo->is_dead;
	sem_post(philo->death);
	return (flag);
}

int	check_dead(t_philo *philo)
{
	long	time_since_meal;

	sem_wait(philo->death);
	if (philo->is_dead)
	{
		sem_post(philo->death);
		return (-1);
	}
	time_since_meal = get_time_ms(philo->last_meal);
	if (time_since_meal >= philo->t_to_die)
	{
		philo->is_dead = 1;
		sem_post(philo->death);
		return (1);
	}
	sem_post(philo->death);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		check;

	philo = (t_philo *)arg;
	while (1)
	{
		check = check_dead(philo);
		if (check == 1)
			return ((void *)&philo->id);
		if (check == -1)
			break ;
		usleep(500);
	}
	return (NULL);
}

void	checker_status_philo(t_philo *philo, t_data *data, int *exit_code)
{
	if (philo->max_meals == 0)
	{
		*exit_code = 0;
		clean_child_data(philo, data);
	}
	else
	{
		*exit_code = philo->id;
		sem_wait(data->print_lock);
		printf(RED "| %-6ld | %-3d | %-16s    |  %s  |\n" RESET,
			get_time_ms(philo->start_time), philo->id, DEAD, "💀");
		clean_child_data(philo, data);
	}
}

int	start_philosopher(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;
	int			exit_code;
	void		*ret_thread;

	philo->pid = getpid();
	if (data->n_philo == 1)
	{
		print_message(philo, FORK, BLUE, "🍴");
		precise_usleep(data->t_to_die, philo);
		print_message(philo, DEAD, RED, "💀");
		clean_child_data(philo, data);
		return (0);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philo))
	{
		clean_child_data(philo, data);
		return (1);
	}
	while (!is_dead(philo))
		if (is_dead(philo) || eat(philo) || sleep_philo(philo) || think(philo))
			break ;
	pthread_join(monitor_thread, &ret_thread);
	checker_status_philo(philo, data, &exit_code);
	exit(exit_code);
}
