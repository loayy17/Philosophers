#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long milliseconds, t_data *data)
{
	long start;
	long elapsed;
	long remaining;

	start = get_time();
	while (1)
	{
		if (is_dead(data))
			break ;
		elapsed = get_time() - start;
		remaining = milliseconds - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 1)
			usleep(remaining * 1000);
	}
}
