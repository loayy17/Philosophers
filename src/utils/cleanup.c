#include "philo.h"

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
}

void	cleanup_resources(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philo[i].thread, NULL);
	destroy_mutexes(data);
	free(data->forks);
	free(data->philo);
}
