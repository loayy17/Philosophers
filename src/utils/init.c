#include "philo.h"

void	free_data(t_data *data, int error)
{
	int	i;

	i = data->n_philos;
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[data->n_philos]);
	if (error == PRINT || error == DEATH || error == PHILOS)
		pthread_mutex_destroy(&data->print_lock);
	if (error == DEATH || error == PHILOS)
		pthread_mutex_destroy(&data->death_lock);
	if (error == PHILOS)
	{
		while (++i < data->n_philos)
			pthread_detach(data->philo[data->n_philos].thread);
	}
	free(data->forks);
	if (error == PHILOS)
		free(data->philo);
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
	int	return_init_mutex;
	int	return_init_philos;

	init_args(data, argc, argv);
	data->start_time = get_time() ;
	data->dead_flag = 0;
	if (data->n_philos < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->n_must_eat < 1))
		return (1);
	return_init_mutex = init_mutexes(data);
	return_init_philos = init_philosophers(data);
	if (return_init_mutex || return_init_philos)
	{
		free_data(data, FORK);
		if (return_init_mutex == PRINT)
			free_data(data, PRINT);
		else if (return_init_mutex == DEATH)
			free_data(data, DEATH);
		else if (return_init_philos == PHILOS)
			free_data(data, PHILOS);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->n_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (FORK);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (PRINT);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (DEATH);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (1);
	i = -1;
	while (++i < data->n_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]))
			return (PHILOS);
	}
	return (0);
}
