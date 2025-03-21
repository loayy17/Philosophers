#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_dead(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->death_lock);
	ret = data->dead_flag;
	pthread_mutex_unlock(&data->death_lock);
	return (ret);
}
