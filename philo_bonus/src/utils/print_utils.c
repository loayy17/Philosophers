/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:13:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/02 15:36:53 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	data = philo->data;
	if (!force)
	{
		sem_wait(data->death_lock);
		if (data->dead_flag)
		{
			sem_post(data->death_lock);
			return ;
		}
		sem_post(data->death_lock);
	}
	timestamp = get_time() - data->start_time;
	if (force)
	{
		sem_wait(data->print_lock);
		printf("| \033[0;31m%-6ld | %d | %s             | 💀\033[0m | \n",
			timestamp, philo->id, msg);
		sem_post(data->print_lock);
	}
	else
	{
		sem_wait(data->death_lock);
		sem_wait(data->print_lock);
		if (data->dead_flag)
		{
			sem_post(data->print_lock);
			sem_post(data->death_lock);
			return ;
		}
		sem_post(data->death_lock);
		if (ft_strcmp(color, "yellow") == 0)
			printf("| \033[0;33m%-6ld | %d | %s      | 🛌 \033[0m| \n",
				timestamp, philo->id, msg);
		else if (ft_strcmp(color, "green") == 0)
			printf("| \033[0;32m%-6ld | %d | %s        | 🍝\033[0m | \n",
				timestamp, philo->id, msg);
		else if (ft_strcmp(color, "blue") == 0)
			printf("| \033[0;34m%-6ld | %d | %s | 🍴\033[0m | \n", timestamp,
				philo->id, msg);
		else if (ft_strcmp(color, "magenta") == 0)
			printf("| \033[0;35m%-6ld | %d | %s      | 🤔\033[0m | \n",
				timestamp, philo->id, msg);
		else
			printf("%-6ld %d %s\n", timestamp, philo->id, msg);
		printf("--------------------------------------\n");
		sem_post(data->print_lock);
	}
}
