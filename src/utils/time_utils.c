#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long milliseconds, t_data *data)
{
	long end_time;

	end_time = get_time() + milliseconds;
	while (get_time() < end_time)
	{
		if (is_dead(data))
			break ;
		usleep(1);
	}
}
