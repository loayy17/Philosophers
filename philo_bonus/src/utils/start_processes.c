/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:37:37 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/05 09:37:39 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(philo->data->meals);
	philo->last_meal = get_time();
	print_status(philo, "has taken a fork", 34, "🍴");
	print_status(philo, "has taken a fork", 34, "🍴");
	print_status(philo, "is eating", 32, "🍝");
	sem_post(philo->data->meals);
	if (data->dead)
		return (1);
	precise_sleep(philo->data->t_eat);
	return (0);
}

void	*is_dead(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(data->meals);
		if (get_time() - philo->last_meal > philo->data->t_die)
		{
			print_status(philo, "died", 31, "💀");
			data->dead = 1;
			sem_wait(data->print);
			free_philos(data);
			exit(1);
		}
		sem_post(data->meals);
		if (philo->data->must_eat > 0 && philo->meals >= philo->data->must_eat)
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	philo_life(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->n_philos == 1)
	{
		print_status(philo, "has taken a fork", 34, "🍴");
		usleep(data->t_die * 1000);
		print_status(philo, "died", 31, "💀");
		free_close(data);
		exit(0);
	}
	pthread_create(&philo->dead, NULL, is_dead, philo);
	philo->last_meal = get_time();
	if (philo->id % 2)
		usleep(100);
	while (!(data->dead))
	{
		grap_forks(data);
		if (eat(philo))
			break ;
		philo->meals++;
		throw_forks(philo);
		if (data->must_eat > 0 && philo->meals >= data->must_eat)
			break ;
		print_status(philo, "is sleeping", 33, "🛌");
		precise_sleep(philo->data->t_sleep);
		print_status(philo, "is thinking", 35, "🤔");
	}
	pthread_join(philo->dead, NULL);
	free_close(data);
	if (data->dead)
		exit(1);
	exit(0);
}

int	start_simulation(t_data *data, int *ret)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philos;
	data->start_time = get_time();
	while (++i < data->n_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			philo_life(&philos[i]);
		else if (philos[i].pid < 0)
		{
			*ret = 4;
			return (1);
		}
	}
	return (0);
}
