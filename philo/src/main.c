/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:40:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:40:54 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_philo_dead(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_lock(&d->philos[i].dead_lock);
		d->philos[i].dead_flag = 1;
		pthread_mutex_unlock(&d->philos[i].dead_lock);
	}
	return (1);
}

static int	check_philosopher(t_philo *p)
{
	long	elapsed;

	pthread_mutex_lock(&p->meal_lock);
	elapsed = get_time(p->last_meal);
	pthread_mutex_unlock(&p->meal_lock);
	pthread_mutex_lock(&p->dead_lock);
	if (!p->dead_flag && elapsed > p->t_die)
	{
		p->death_time = get_time(p->start_time);
		p->dead_flag = 1;
		pthread_mutex_unlock(&p->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->dead_lock);
	return (0);
}

static int	check_meals(t_data *d)
{
	int	i;
	int	all;

	if (d->n_must_eat < 0)
		return (0);
	all = 1;
	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_lock(&d->philos[i].meal_lock);
		if (d->philos[i].meals_eaten < d->n_must_eat)
			all = 0;
		pthread_mutex_unlock(&d->philos[i].meal_lock);
		if (!all)
			break ;
	}
	if (all)
		set_philo_dead(d);
	return (all);
}

static int	monitor_loop(t_data *d)
{
	int	i;
	int	dead_philo;

	dead_philo = 0;
	while (1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			dead_philo = i + 1;
			if (check_philosopher(&d->philos[i]) && set_philo_dead(d))
				return (dead_philo);
		}
		if (check_meals(d))
			return (0);
		usleep(500);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		philo_dead;
	long	death_time;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	philo_dead = monitor_loop(&data);
	if (philo_dead)
	{
		death_time = get_time(data.philos[philo_dead - 1].start_time);
		printf(RED "| %-6ld | %-3d | %-16s    |  💀  |\n" RESET, death_time,
			philo_dead, DEAD);
	}
	cleanup_resources(&data);
	return (0);
}
