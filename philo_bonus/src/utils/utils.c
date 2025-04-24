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
			return(philo->id);
		usleep(100);
	}
	return (0);
}

int    print_message(t_philo *philo, char *status, char *color, char *emoji)
{
	long	time;

	time = get_time_ms(philo->start_time);
	sem_wait(philo->print_lock);
	sem_wait(philo->death);
	if (philo->is_dead)
	{
		sem_post(philo->print_lock);
		sem_post(philo->death);
		return (1);
	}
	printf("%s| %-6ld | %-3d | %-16s    |  %s  |\n"RESET,color, time, philo->id, status, emoji);

	sem_post(philo->print_lock);
	sem_post(philo->death);
	return (0);
}
// {
// 	long	time;
	
// 	time = get_time_ms(philo->start_time);
// 	sem_wait(philo->death);
// 	sem_wait(philo->print_lock);
// 	if (*philo->is_dead)
// 	{
// 		sem_post(philo->death);
// 		sem_post(philo->print_lock);
// 		return (1);
// 	}
// 	if (type == SLEEP)
// 		printf(YELLOW "| %-6ld | %d | is sleeping    | 🛌 | \n" RESET, time,
// 			philo->id);
// 	else if (type == EAT)
// 		printf(GREEN "| %-6ld | %d | is eating      | 🍝 | \n" RESET, time,
// 			philo->id);
// 	else if (type == THINK)
// 		printf(MAGENTA "| %-6ld | %d | is thinking    | 🍴 | \n" RESET, time,
// 			philo->id);
// 	else if (type == FORK)
// 		printf(BLUE "| %-6ld | %d | is taking fork | 🍴 | \n" RESET, time,
// 			philo->id);
// 	else if (type == DEAD)
// 		printf(RED "| %-6ld | %d | is dead         | 💀 | \n" RESET, time,
// 			philo->id);	
// 	sem_post(philo->death);	
// 	sem_post(philo->print_lock);		
// 	return (0);
// }
