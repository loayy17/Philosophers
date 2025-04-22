/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_args(t_data *d, int argc, char **argv)
{
	d->n_philos   = atoi(argv[1]);
	d->t_die      = atol(argv[2]);  /* note: stored per-philo below */
	d->t_eat      = atol(argv[3]);
	d->t_sleep    = atol(argv[4]);
	d->n_must_eat = (argc == 6) ? atoi(argv[5]) : -1;
	d->start_time = get_time(0);
}

static int init_mutexes(t_data *d)
{
	int i;

	d->forks = malloc(sizeof(pthread_mutex_t) * d->n_philos);
	if (!d->forks)
		return (1);
	for (i = 0; i < d->n_philos; i++)
		if (pthread_mutex_init(&d->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&d->print_lock, NULL))
		return (1);
	return (0);
}

static void init_philo(t_data *d, int i)
{
	t_philo *p = &d->philos[i];

	p->id          = i + 1;
	p->t_die       = d->t_die;
	p->t_eat       = d->t_eat;
	p->t_sleep     = d->t_sleep;
	p->start_time  = d->start_time;
	p->last_meal   = d->start_time;
	p->meals_eaten = 0;
	p->dead_flag   = 0;
	if (pthread_mutex_init(&p->meal_lock, NULL) ||
		pthread_mutex_init(&p->dead_lock, NULL))
	{
		ft_print_error("Error: Failed to initialize philosopher mutexes\n");
		return;
	}
	p->left_fork   = &d->forks[i];
	p->right_fork  = &d->forks[(i + 1) % d->n_philos];
	p->print_lock  = &d->print_lock;
}

static int spawn_philos(t_data *d)
{
	int i;

	d->philos = malloc(sizeof(t_philo) * d->n_philos);
	if (!d->philos)
		return (1);
	for (i = 0; i < d->n_philos; i++)
	{
		init_philo(d, i);
		if (pthread_create(&d->philos[i].thread,
			NULL, philo_routine, &d->philos[i]))
			return (1);
	}
	return (0);
}

int init_data(t_data *d, int argc, char **argv)
{
	init_args(d, argc, argv);
	if (init_mutexes(d))
		return (1);
	if (spawn_philos(d))
	{
		cleanup_resources(d);
		return (1);
	}
	return (0);
}
