#include "philo.h"

static int	check_philosopher(t_data *data, int i)
{
	long	current_time;
	int		dead;

	pthread_mutex_lock(&data->death_lock);
	current_time = get_time();
	dead = 0;
	if (current_time - data->philo[i].last_meal > data->t_die)
	{
		data->dead_flag = 1;
		print_message(&data->philo[i], "died");
		dead = 1;
	}
	pthread_mutex_unlock(&data->death_lock);
	return (dead);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_must_eat == -1)
		return (0);
	all_ate = 1;
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->philo[i].meals_eaten < data->n_must_eat)
			all_ate = 0;
		pthread_mutex_unlock(&data->death_lock);
		if (!all_ate)
			break ;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->death_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->n_philos)
		{
			if (check_philosopher(data, i) || check_meals(data))
				return (NULL);
		}
		usleep(1000);
	}
}

void	start_monitor(t_data *data)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitor_routine, data);
	pthread_join(monitor, NULL);
}
