/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:09 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/03 18:26:42 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (data->philo[i].pid > 0)
		{
			kill(data->philo[i].pid, 9);
			waitpid(data->philo[i].pid, NULL, 0);
		}
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
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->death_lock);
	sem_unlink("print_lock");
	sem_unlink("death_lock");
	sem_unlink("forks");
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
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
	ret = init_semaphore(data);
	if (ret == 0)
		ret = init_philosophers(data);
	if (ret)
		free_data(data, ret);
	return (ret != 0);
}

int	init_philosophers(t_data *data)
{
	int		i;
	int		ret;
	pid_t	pid;

	ret = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (PHILOS);
	i = -1;
	while (++i < data->n_philos && ret == 0)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meals_eaten = 0;
		pid = fork();
		if (pid == 0)
		{
			philo_routine(&data->philo[i]);
			free_philos(data);
			free_data(data, PHILOS);
			exit (0);
		}
		else if (pid < 0)
		{
			free_philos(data);
			return (1);
		}
		data->philo[i].pid = pid;
	}
	if (ret != 0)
		free_philos(data);
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

int	init_semaphore(t_data *data)
{
	sem_unlink("print_lock");
	sem_unlink("death_lock");
	sem_unlink("forks");

	data->print_lock = sem_open("print_lock", O_CREAT, 0644, 1);
	data->death_lock = sem_open("death_lock", O_CREAT, 0644, 1);
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philos);
	if (data->print_lock == SEM_FAILED || data->death_lock == SEM_FAILED
		|| data->forks == SEM_FAILED)
		return (1);
	return (0);
}