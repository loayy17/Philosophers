#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	int	flag;

	sem_wait(philo->death);
	flag = philo->is_dead;
	sem_post(philo->death);
	return (flag);
}

int	check_dead(t_philo *philo)
{
	long	time_since_meal;

	sem_wait(philo->death);
	if (philo->is_dead)
	{
		sem_post(philo->death);
		return (-1);
	}
	time_since_meal = get_time_ms(philo->last_meal);
	if (time_since_meal >= philo->t_to_die)
	{
		philo->is_dead = 1;
		sem_post(philo->death);
		return (1);
	}
	sem_post(philo->death);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		check;

	philo = (t_philo *)arg;
	while (1)
	{
		check = check_dead(philo);
		if (check == 1)
			return ((void *)&philo->id);
		if (check == -1)
			break ;
		usleep(500);
	}
	return (NULL);
}

int	grap_forks(t_philo *philo)
{
	sem_wait(philo->n_philo_eat);
	sem_wait(philo->forks);
	if (print_message(philo, FORK, MAGENTA, "🍴"))
		return (-1);
	sem_wait(philo->forks);
	if (print_message(philo, FORK, MAGENTA, "🍴"))
		return (-1);
	return (0);
}

int	throw_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->n_philo_eat);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->max_meals == 0 || is_dead(philo))
		return (-1);
	if (grap_forks(philo))
		return (-1);
	if (print_message(philo, EAT, GREEN, "🍝"))
		return (-1);
	sem_wait(philo->death);
	philo->last_meal = get_time_ms(0);
	if (philo->max_meals > 0)
		philo->max_meals--;
	sem_post(philo->death);
	if (precise_usleep(philo->t_to_eat, philo))
		return (-1);
	if (throw_forks(philo))
		return (-1);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_message(philo, SLEEP, YELLOW, "🛌"))
		return (-1);
	if (precise_usleep(philo->t_to_sleep, philo))
		return (-1);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_message(philo, THINK, MAGENTA, "🤔"))
		return (-1);
	if (precise_usleep(1, philo))
		return (-1);
	return (0);
}
int	start_philosopher(t_philo *philo, t_data *data)
{
	pthread_t monitor_thread;
	int exit_code;
	void *ret_thread;
	philo->pid = getpid();
	if (data->n_philo == 1)
	{
		print_message(philo, FORK, BLUE, "🍴");
		precise_usleep(data->t_to_die, philo);
		print_message(philo, DEAD, RED, "💀");
		clean_child_data(philo, data);
		return (0);
	}

	if (pthread_create(&monitor_thread, NULL, monitor_routine, philo))
	{
		clean_child_data(philo, data);
		return (1);
	}
	while (!is_dead(philo))
	{
		if (is_dead(philo))
			break ;
		if (eat(philo))
			break ;
		if (sleep_philo(philo))
			break ;
		if (think(philo))
			break ;
	}
	pthread_join(monitor_thread, &ret_thread);
	if (philo->max_meals == 0)
	{
		exit_code =  0;
		clean_child_data(philo, data);
	}
	else
	{
		exit_code =  philo->id;
		sem_wait(data->print_lock);
		printf(RED "| %-6ld | %-3d | %-16s    |  %s  |\n" RESET, get_time_ms(philo->start_time),
			philo->id, DEAD, "💀");
		
		clean_child_data(philo, data);
	}
	exit(exit_code);
}