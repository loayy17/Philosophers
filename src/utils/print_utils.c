/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:13:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/11 22:41:51 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_colored(char *color, t_philo *philo, char *msg, t_data *data)
{
	long	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	if (ft_strcmp(color, "yellow") == 0)
		printf("| \033[0;33m%-6ld | %d | %s      | 🛌 \033[0m| \n", timestamp,
			philo->id, msg);
	else if (ft_strcmp(color, "green") == 0)
		printf("| \033[0;32m%-6ld | %d | %s        | 🍝\033[0m | \n", timestamp,
			philo->id, msg);
	else if (ft_strcmp(color, "blue") == 0)
		printf("| \033[0;34m%-6ld | %d | %s | 🍴\033[0m | \n", timestamp,
			philo->id, msg);
	else if (ft_strcmp(color, "magenta") == 0)
		printf("| \033[0;35m%-6ld | %d | %s      | 🤔\033[0m | \n", timestamp,
			philo->id, msg);
	else if (ft_strcmp(color, "red") == 0)
		printf("| \033[0;31m%-6ld | %d | %s             | 💀\033[0m | \n",
			timestamp, philo->id, msg);
	else
		printf("%-6ld %d %s\n", timestamp, philo->id, msg);
	printf("--------------------------------------\n");
	pthread_mutex_unlock(&data->print_lock);
}

void	print_message(t_philo *philo, char *msg, char *color, int force)
{
	t_data	*data;

	data = philo->data;
	if (!force && dead_lock_checker(data))
		return ;
	if (force)
		print_colored(color, philo, msg, data);
	else if (!dead_lock_checker(data))
		print_colored(color, philo, msg, data);
	else
		return ;
}
