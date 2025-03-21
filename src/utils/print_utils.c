/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:13:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/03/21 20:23:31 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	long	timestamp;
	long	actual_time;	
	
	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_dead(philo->data))
	{
		actual_time = get_time();
		printf("%ld %ld\n", actual_time , philo->data->start_time);
		timestamp = actual_time - philo->data->start_time;
		printf("%-6ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
