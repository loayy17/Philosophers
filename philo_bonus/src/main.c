#include "philo_bonus.h"

void	set_all_philos_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		sem_wait(data->death);
		data->philos[i].is_dead = 1;
		sem_post(data->death);
	}
}

void	wait_children(t_data *data)
{
	int		i;
	int		status;
	int		id;
	int		meals_completed;

	i = -1;
	meals_completed = 0;
	while (++i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		id = (((status)&0xff00) >> 8);
		if (id != 0)
		{
			set_all_philos_dead(data);
			break ;
		}
		else
		{
			meals_completed++;
		}
	}
	if (id)
	{
		kill_children(data, data->n_philo);
		sem_post(data->print_lock);
	}
	if (meals_completed == data->n_philo)
		kill_children(data, data->n_philo);
	cleanup_simulation(data);	
}

int	start_process(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
		{
			kill_children(data, i);
			ft_print_error("Error: Fork failed\n");
			return (1);
		}
		if (data->philos[i].pid == 0)
		{
			start_philosopher(&data->philos[i], data);
			exit(0);
		}
	}
	wait_children(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data data;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
	{
		cleanup_simulation(&data);
		return (1);
	}
	if (start_process(&data))
	{
		cleanup_simulation(&data);
		return (1);
	}
	cleanup_simulation(&data);
	return (0);
}