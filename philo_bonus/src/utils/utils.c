/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/04/12 18:02:46 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/12 18:02:46 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	kill_children(t_data *data, int i)
{
	int	j;
	(void)i;

	j = -1;
	while (++j < data->n_philo)
	{
		if(data->philos[j].pid != 0)
			kill(data->philos[j].pid, SIGKILL);
	}
}

long	get_time_ms(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start);
}

int	precise_usleep(long time_wait,t_philo *philo)
{
	long	start;

	start = get_time_ms(0);
	while (get_time_ms(start) < time_wait)
	{
		if (check_dead(philo))
			return(-1);
		if (get_time_ms(philo->last_meal) > philo->t_to_die)
			usleep(1);
	}
	return (0);
}

int	print_message(int type, t_philo *philo)
{
	long	time;
	
	time = get_time_ms(philo->start_time);
	if (check_dead(philo))
		return (-1);
	if (type == SLEEP && !check_dead(philo))
		printf(YELLOW "| %-6ld | %d | is sleeping    | 🛌 | \n" RESET, time,
			philo->id);
	else if (type == EAT && !check_dead(philo))
		printf(GREEN "| %-6ld | %d | is eating      | 🍝 | \n" RESET, time,
			philo->id);
	else if (type == THINK && !check_dead(philo))
		printf(MAGENTA "| %-6ld | %d | is thinking    | 🍴 | \n" RESET, time,
			philo->id);
	else if (type == FORK && !check_dead(philo))
		printf(BLUE "| %-6ld | %d | is taking fork | 🍴 | \n" RESET, time,
			philo->id);
	else if (type == DEAD)
		printf(RED "| %-6ld | %d | is dead         | 💀 | \n" RESET, time,
			philo->id);		
	return (0);
}
