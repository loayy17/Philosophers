#include "philo_bonus.h"

void	grab_forks(t_data *data, int id)
{
	sem_wait(data->forks);
	sem_wait(data->fork_mutex);
	print_action(data, id, "has taken a fork");
	sem_wait(data->forks);
	print_action(data, id, "has taken a fork");
	sem_post(data->fork_mutex);
}

void	throw_forks(t_data *data, t_philo *philo)
{
	sem_post(data->forks);
	sem_post(data->forks);
	sem_wait(philo->meal);
	philo->last_meal = get_time(data->start_time);
	sem_post(philo->meal);
}

void	print_action(t_data *data, int id, char *msg)
{
	sem_wait(data->print);
	printf("%ld %d %s\n", get_time(data->start_time), id, msg);
	sem_post(data->print);
}

void	eat(t_data *data, int id)
{
	sem_wait(data->forks);
	print_action(data, id, "has taken a fork");
	sem_wait(data->forks);
	print_action(data, id, "has taken a fork");
	print_action(data, id, "is eating");
	precise_sleep(data->t_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		id;

	data = (t_data *)arg;
	id = data->max_meals;
	while (1)
	{
		sem_wait(data->death_sem);
		if (get_time(data->start_time) > data->t_die)
		{
			print_action(data, id, "died");
			exit(1);
		}
		sem_post(data->death_sem);
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_thread(void *arg)
{
	t_monitor_philo	*m;
	long			now;

	m = (t_monitor_philo *)arg;
	while (1)
	{
		now = get_time(*m->start_time);
		if (now - *m->last_meal > m->t_die)
		{
			sem_wait(m->print);
			printf("%ld %d died\n", now, m->id);
			sem_post(m->death);
			sem_post(m->meal);
			free(m);
			return (NULL);
		}
		sem_post(m->meal);
		usleep(1000);
	}
	return (NULL);
}
void	monitor_philo(t_philo *philo, t_data *data)
{
	t_monitor_philo	*m;
	pthread_t		monitor_philo;

	m = malloc(sizeof(t_monitor_philo));
	if (!m)
		return ;
	m->id = philo->id;
	m->t_die = data->t_die;
	m->start_time = &data->start_time;
	m->last_meal = &philo->last_meal;
	m->meal = philo->meal;
	m->death = data->death_sem;
	m->print = data->print;
	pthread_create(&monitor_philo, NULL, monitor_thread, m);
	pthread_detach(monitor_philo);
}
void	philo_routine(t_data *data, int id)
{
	t_philo	*philo;

	philo = init_philo(id);
	if (!philo)
		exit(1);
	monitor_philo(philo, data);
	while (1)
	{
		print_action(data, id, "is thinking");
		grab_forks(data, id);
		print_action(data, id, "is eating");
		precise_sleep(data->t_eat);
		++philo->meals_eaten;
		throw_forks(data, philo);
		print_action(data, id, "is thinking");
		if (data->max_meals != -1 && philo->meals_eaten == data->max_meals)
			sem_post(data->meals);
		print_action(data, id, "is sleeping");
		precise_sleep(data->t_sleep);
	}
}

void	*death_monitor(void *arg)
{
	t_data	*data;

	data = arg;
	sem_wait(data->death_sem);
	for (int i = 0; i < data->n_philos; i++)
		sem_post(data->meals);
	return (NULL);
}

void	*meal_monitor(void *arg)
{
	t_data	*data;

	data = arg;
	for (int i = 0; i < data->n_philos; i++)
		sem_wait(data->meals);
	sem_post(data->death_sem);
	return (NULL);
}

void	start_processes(t_data *data)
{
	int i;
	pthread_t t1;
	pthread_t t2;

	i = -1;
	while (++i < data->n_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			philo_routine(data, i + 1);
			exit(0);
		}
	}
	pthread_create(&t1, NULL, death_monitor, data);
	pthread_create(&t2, NULL, meal_monitor, data);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	for (int i = 0; i < data->n_philos; i++)
		kill(data->pids[i], 9);
	cleanup(data);
	exit(0);
}