#include "philo_bonus.h"


long	get_time(long from)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - from);
}

void	precise_sleep(long time)
{
	long	start_time;

	start_time = get_time(0);
	while (get_time(start_time) < time)
		usleep(1);
}
int	print_stderr(char *msg, int code)
{
	printf("Error: %s\n", msg);
	return (code);
}