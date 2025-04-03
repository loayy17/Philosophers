/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:03:48 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/02 15:37:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	timevalue;

	gettimeofday(&timevalue, NULL);
	return (timevalue.tv_sec * 1000 + timevalue.tv_usec / 1000);
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