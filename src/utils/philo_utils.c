#include "philo.h"


void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->death_lock);
}

int	all_meals_completed(t_data *data)
{
	int i;
	int all_ate;

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
	return (all_ate);
}