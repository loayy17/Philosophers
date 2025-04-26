#include "philo_bonus.h"

void	clean_child_data(t_philo *philo, t_data *data)
{
	sem_close(philo->forks);
	sem_close(philo->n_philo_eat);
	sem_close(philo->death);
	sem_close(philo->print_lock);
	free(data->philos);
}

void	cleanup_simulation(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->n_philo_eat)
		sem_close(data->n_philo_eat);
	if (data->death)
		sem_close(data->death);
	if (data->print_lock)
		sem_close(data->print_lock);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	sem_unlink("/forks");
	sem_unlink("/n_philo_eat");
	sem_unlink("/death");
	sem_unlink("/print");
}