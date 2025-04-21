/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 05:35:57 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/21 05:42:00 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_error(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
}

void	print_message(t_philo *philo, int type)
{
	pthread_mutex_lock(philo->print_lock);
	if (checker_dead_lock(philo) && type != DEAD)
	{
		pthread_mutex_unlock(philo->print_lock);
		return ;
	}
	if (type == DEAD)
		printf(RED "%-6ld %d died\n" RESET, get_time(philo->start_time),
			philo->id);
	else if (type == FORKS)
		printf(BLUE "%-6ld %d has taken a fork\n" RESET,
			get_time(philo->start_time), philo->id);
	else if (type == EAT)
		printf(GREEN "%-6ld %d is eating\n" RESET, get_time(philo->start_time),
			philo->id);
	else if (type == SLEEP)
		printf(YELLOW "%-6ld %d is sleeping\n" RESET,
			get_time(philo->start_time), philo->id);
	else if (type == THINK)
		printf(MAGENTA "%-6ld %d is thinking\n" RESET,
			get_time(philo->start_time), philo->id);
	pthread_mutex_unlock(philo->print_lock);
}

int	is_dead(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->death_lock);
	ret = *philo->dead_flag;
	pthread_mutex_unlock(philo->death_lock);
	return (ret);
}

long	get_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time);
}

void	precise_usleep(long milliseconds, t_philo *philo)
{
	long start;

	start = get_time(0);
	while (get_time(start) < milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(1);
	}
}