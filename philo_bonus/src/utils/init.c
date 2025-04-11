#include "philo_bonus.h"

int	init_args(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]) * 1000;
	data->t_eat = ft_atoi(argv[3]) * 1000;
	data->t_sleep = ft_atoi(argv[4]) * 1000;
	data->max_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;
	data->death = 0;
	return (0);
}

int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FORK_MUTEX);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->n_philos);
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	data->meals = sem_open(SEM_MEALS, O_CREAT, 0644, 0);
	data->death_sem = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	data->fork_mutex = sem_open(SEM_FORK_MUTEX, O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->meals == SEM_FAILED || data->death_sem == SEM_FAILED
		|| data->fork_mutex == SEM_FAILED)
		return (3);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	init_args(data, argc, argv);
	if (check_args(data))
		return (1);
	if (init_semaphores(data))
		return (3);
	data->start_time = get_time(0);
	data->pids = malloc(sizeof(pid_t) * data->n_philos);
	if (!data->pids)
		return (2);
	return (0);
}

t_philo	*init_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal = get_time(0);
	sem_unlink(SEM_MEAL_SEM);
	philo->meal = sem_open(SEM_MEAL_SEM, O_CREAT, 0644, 1);
	if (philo->meal == SEM_FAILED)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
