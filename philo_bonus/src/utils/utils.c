#include "philo_bonus.h"

int	ft_print_error(char *msg)
{
	while (*msg)
		write(2, msg++, 1);
	return (1);
}

void	kill_children(t_data *data, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, 9);
}

long	get_time_ms(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start);
}

int	precise_usleep(long time_wait, t_philo *philo)
{
	long	start;

	start = get_time_ms(0);
	while (get_time_ms(start) < time_wait)
	{
		if (philo && is_dead(philo))
			return (1);
		usleep(500);
	}
	return (0);
}

int	print_message(t_philo *philo, char *status, char *color, char *emoji)
{
    long time;

    sem_wait(philo->print_lock);
    sem_wait(philo->death);
    if (philo->is_dead)
    {
        sem_post(philo->death);
        sem_post(philo->print_lock);
        return (1);
    }
    time = get_time_ms(philo->start_time);
    printf("%s| %-6ld | %-3d | %-16s    |  %s  |\n" RESET, color, time,
        philo->id, status, emoji);
    sem_post(philo->death);
    sem_post(philo->print_lock);
    return (0);
}