/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_print_error(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
}

long get_time(long start)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}

void precise_usleep(long ms, t_philo *p)
{
	long begin = get_time(0);

	while (get_time(begin) < ms)
	{
		pthread_mutex_lock(&p->dead_lock);
		if (p->dead_flag)
		{
			pthread_mutex_unlock(&p->dead_lock);
			break;
		}
		pthread_mutex_unlock(&p->dead_lock);
		usleep(1);
	}
}

int is_dead(t_philo *p)
{
	int flag;
	pthread_mutex_lock(&p->dead_lock);
	flag = p->dead_flag;
	pthread_mutex_unlock(&p->dead_lock);
	return (flag);
}

int print_message(t_philo *philo, char *status, char *color, char *emoji)
{
    long time;

    pthread_mutex_lock(philo->print_lock);
	pthread_mutex_lock(&philo->dead_lock);
    if (philo->dead_flag) {
        pthread_mutex_unlock(philo->print_lock);
		pthread_mutex_unlock(&philo->dead_lock);
        return (1);
    }
    time = get_time(philo->start_time);
    printf("%s| %-6ld | %-3d | %-16s    |  %s  |\n"RESET,color, time, philo->id, status, emoji);
    pthread_mutex_unlock(philo->print_lock);
    pthread_mutex_unlock(&philo->dead_lock);
	return (0);
}
