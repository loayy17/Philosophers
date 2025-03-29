/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:09 by lalhindi          #+#    #+#             */
/*   Updated: 2025/03/29 20:53:56 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"
#include <fcntl.h>


void free_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_detach(data->philo[i].thread);
	}
}
void	free_data(t_data *data, int error)
{
	if (data->forks)
	{
		cleanup_resources(data);
	}
	if (error >= PRINT)
	{
		sem_close(data->print_lock);
		sem_close(data->death_lock);
	}
	if (error == PHILOS && data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
}

void	cleanup_resources(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		sem_close(data->forks[i]);
	sem_close(data->print_lock);
	sem_close(data->death_lock);
	free(data->philo);
	free(data->forks);
}
void	init_args(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_must_eat = -1;
	if (argc == 6)
		data->n_must_eat = ft_atoi(argv[5]);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	ret;

	ret = 0;
	init_args(data, argc, argv);
	data->start_time = get_time();
	data->dead_flag = 0;
	if (data->n_philos < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->n_must_eat < 1))
		return (1);
	ret = init_mutexes(data);
	if (ret == 0)
		ret = init_philosophers(data);
	if (ret)
		free_data(data, ret);
	return (ret != 0);
}

int	init_philosophers(t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (PHILOS);
	i = -1;
	while (++i < data->n_philos && ret == 0)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = data->forks[i];
		data->philo[i].right_fork = data->forks[(i + 1) % data->n_philos];
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]))
			ret = PHILOS;
	}
	if (ret != 0)
	{
		free_philos(data);
	}
	return (ret);
}
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nb;

	nb = n;
	len = 1;
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	init_mutexes(t_data *data)
{
	int i;
	sem_unlink("print_lock");
	sem_unlink("death_lock");

	data->print_lock = sem_open("print_lock", O_CREAT, 0644, 1);
	data->death_lock = sem_open("death_lock", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED || data->death_lock == SEM_FAILED)
		return (1);
	data->forks = malloc(sizeof(sem_t) * data->n_philos);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->n_philos)
	{
		sem_unlink(ft_itoa(i));
		data->forks[i] = sem_open(ft_itoa(i), O_CREAT, 0644, 1);
		if (data->forks[i] == SEM_FAILED)
			return (1);
	}	
	return (0);
}