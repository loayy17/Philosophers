#include "philo_bonus.h"

void	error_message(int error_code)
{
	if (error_code == 1)
		write(2, "Error: Wrong number of arguments\n", 33);
	else if (error_code == 2)
		write(2, "Error: Invalid arguments\n", 25);
	else if (error_code == 3)
		write(2, "Error: Failed to create semaphore\n", 34);
	else if (error_code == 4)
		write(2, "Error: Failed to create process\n", 32);
	else if (error_code == 5)
		write(2, "Error: Failed to join process\n", 30);
	else if (error_code == 6)
		write(2, "Error: Failed to allocate memory\n", 33);
	else
		write(2, "Unknown error occurred\n", 23);
}

void	kill_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		if (data->pids[i] != 0)
			kill(data->pids[i], SIGKILL);
}

void	cleanup(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->meals);
	sem_close(data->death_sem);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DEATH);
	if (data->pids)
		free(data->pids);
	free(data);
}