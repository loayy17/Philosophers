#include "philo.h"

static void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->death_lock);
	if(data->dead_flag)
	{
		pthread_mutex_unlock(&data->death_lock);
		return ;
	}
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->death_lock);
	print_message(philo, "has taken a fork", "blue", 0);
	print_message(philo, "has taken a fork", "blue", 0);
	print_message(philo, "is eating", "green", 0);
	precise_usleep(data->t_eat, data);
}

static void	drop_forks(pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
}

static int	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_dead(philo->data))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_dead(philo->data))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork", "blue", 0);
		pthread_mutex_unlock(philo->left_fork);
		if (is_dead(philo->data))
			precise_usleep(philo->data->t_die, philo->data);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		if (grab_forks(philo))
			break ;
		eat(philo);
		drop_forks(philo->left_fork, philo->right_fork);
		// pthread_mutex_lock(&philo->data->print_lock);
		// if (philo->data->dead_flag == 0)
		// {
			print_message(philo, "is sleeping", "yellow", 0);
		// }
		// pthread_mutex_unlock(&philo->data->print_lock);

		
		precise_usleep(philo->data->t_sleep, philo->data);
		print_message(philo, "is thinking", "magenta", 0);
	}
	return (NULL);
}
