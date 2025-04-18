/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:13:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/16 21:24:35 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_colored(int id, int type, t_data *data)
{
	long	time;

	time = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	if (type == DEAD)
	{
		printf(RED "| %-6ld | %-6d | is dead        | 💀 | \n" RESET, time, id);
	}
	else if (type == SLEEP)
		printf(YELLOW "| %-6ld | %-6d | is sleeping    | 🛌 | \n" RESET, time,
			id);
	else if (type == EAT)
		printf(GREEN "| %-6ld | %-6d | is eating      | 🍝 | \n" RESET, time,
			id);
	else if (type == THINK)
		printf(MAGENTA "| %-6ld | %-6d | is thinking    | 🍴 | \n" RESET, time,
			id);
	else if (type == FORK)
		printf(BLUE "| %-6ld | %-6d | is taking fork | 🍴 | \n" RESET, time, id);
	printf("-----------------------------------------\n");
	pthread_mutex_unlock(&data->print_lock);
}

void	print_message(t_philo *philo, int type, int force)
{
	t_data	*data;

	data = philo->data;
	if (!force && dead_lock_checker(data))
		return ;
	if (force || !dead_lock_checker(data))
		print_colored(philo->id, type, data);
	else
		return ;
}
