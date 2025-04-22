/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_philosopher(t_philo *p)
{
	long elapsed;

	pthread_mutex_lock(&p->meal_lock);
	elapsed = get_time(p->last_meal);
	pthread_mutex_lock(&p->dead_lock);
	if (!p->dead_flag && elapsed > p->t_die)
	{
		p->dead_flag = 1;
		p->death_time = get_time(p->start_time);
		pthread_mutex_unlock(&p->dead_lock);
		pthread_mutex_unlock(&p->meal_lock);
		return 1;
	}
	pthread_mutex_unlock(&p->dead_lock);
	pthread_mutex_unlock(&p->meal_lock);
	return 0;
}

static int check_meals(t_data *d)
{
	int i, all;

	if (d->n_must_eat < 0)
		return 0;
	all = 1;
	for (i = 0; i < d->n_philos; i++)
	{
		pthread_mutex_lock(&d->philos[i].meal_lock);
		if (d->philos[i].meals_eaten < d->n_must_eat)
			all = 0;
		pthread_mutex_unlock(&d->philos[i].meal_lock);
		if (!all) break;
	}
	if (all)
		for (i = 0; i < d->n_philos; i++)
		{
			pthread_mutex_lock(&d->philos[i].dead_lock);
			d->philos[i].dead_flag = 1;
			pthread_mutex_unlock(&d->philos[i].dead_lock);
		}
	return all;
}

static void monitor_loop(t_data *d)
{
	int i;
	int dead_philo = 0;
	while (1)
	{
		for (i = 0; i < d->n_philos; i++)
			if (check_philosopher(&d->philos[i]))
			{
				dead_philo = i + 1;
				for (int j = 0; j < d->n_philos; j++)
				{

					pthread_mutex_lock(&d->philos[j].dead_lock);
					d->philos[j].dead_flag = 1;
					pthread_mutex_unlock(&d->philos[j].dead_lock);
				}
				pthread_mutex_lock(&d->print_lock);
				printf(RED "| %-6ld | %d | is dead         | 💀 | \n" RESET,
					d->philos[dead_philo - 1].death_time, dead_philo);
		pthread_mutex_unlock(&d->print_lock);
				return;
			}
		if (check_meals(d))
			return;
		usleep(100);
	}
}

int main(int argc, char **argv)
{
	t_data data;

	if (validate_args(argc, argv))
		return 1;
	if (init_data(&data, argc, argv))
		return 1;

	monitor_loop(&data);
	cleanup_resources(&data);
	return 0;
}
