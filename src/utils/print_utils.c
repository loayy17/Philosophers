/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:13:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/03/24 01:05:32 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	print_message(t_philo *philo, char *msg, char *color, int force)
{
	t_data	*data;
	long	timestamp;
	(void)force;
	data = philo->data;
	if (!force)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->death_lock);
		
	}
	if (data->dead_flag)
	{
		
		return ;
	}
	pthread_mutex_lock(&data->print_lock);
	
	timestamp = get_time() - data->start_time;
	if(data->dead_flag)
	{
		pthread_mutex_unlock(&data->print_lock);
		return ;
	}
	if (!data->dead_flag && ft_strcmp(color, "red") == 0)
		printf("\033[0;31m%-6ld %d %s\033[0m\n", timestamp, philo->id, msg);
	else if (!data->dead_flag && ft_strcmp(color, "yellow") == 0)
		printf("\033[0;33m%-6ld %d %s\033[0m\n", timestamp, philo->id, msg);
	else if (!data->dead_flag && ft_strcmp(color, "green") == 0)
		printf("\033[0;32m%-6ld %d %s\033[0m\n", timestamp, philo->id, msg);
	else if (!data->dead_flag && ft_strcmp(color, "blue") == 0)
		printf("\033[0;34m%-6ld %d %s\033[0m\n", timestamp, philo->id, msg);
	else if (!data->dead_flag && ft_strcmp(color, "magenta") == 0)
		printf("\033[0;35m%-6ld %d %s\033[0m\n", timestamp, philo->id, msg);
	else
		printf("%-6ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&data->print_lock);
}
