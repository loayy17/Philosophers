/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:37:52 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/05 14:44:03 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	grap_forks(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
}

void	throw_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *msg, int color, char *emoji)
{
	t_data	*data;
	long	timestamp;

	data = philo->data;
	timestamp = get_time() - data->start_time;
	if (data->dead)
		return ;
	sem_wait(data->print);
	printf("| \033[0;%dm%-6ld | %d | %-16s | %s \033[0m|\n", color, timestamp,
		philo->id, msg, emoji);
	printf("--------------------------------------\n");
	sem_post(data->print);
}
