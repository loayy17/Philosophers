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

void print_message(t_philo *philo, int type)
{
	long	time;
	
	time = get_time(philo->start_time);
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->print_lock);
	if (type == SLEEP)
		printf(YELLOW "| %-6ld | %d | is sleeping    | 🛌 | \n" RESET, time,
			philo->id);
	else if (type == EAT)
		printf(GREEN "| %-6ld | %d | is eating      | 🍝 | \n" RESET, time,
			philo->id);
	else if (type == THINK)
		printf(MAGENTA "| %-6ld | %d | is thinking    | 🍴 | \n" RESET, time,
			philo->id);
	else if (type == FORKS)
		printf(BLUE "| %-6ld | %d | is taking fork | 🍴 | \n" RESET, time,
			philo->id);
	else if (type == DEAD)
		printf(RED "| %-6ld | %d | is dead         | 💀 | \n" RESET, time,
			philo->id);				
	pthread_mutex_unlock(philo->print_lock);		
}
