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

long	get_time_ms(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start);
}

void	precise_usleep(long ms)
{
	long	start;

	start = get_time_ms(0);
	while (get_time_ms(0) - start < ms)
		usleep(1);
}

void	print_message(int id, int type, long start, sem_t *print)
{
	long	time;

	time = get_time_ms(start);
	sem_wait(print);
	if (type == SLEEP)
		printf(YELLOW "| %-6ld | %d | is sleeping    | 🛌 | \n" RESET, time, id);
	else if (type == EAT)
		printf(GREEN "| %-6ld | %d | is eating      | 🍝 | \n" RESET, time, id);
	else if (type == THINK)
		printf(MAGENTA "| %-6ld | %d | is thinking    | 🍴 | \n" RESET, time,
			id);
	else if (type == FORK)
		printf(BLUE "| %-6ld | %d | is taking fork | 🍴 | \n" RESET, time, id);
	else if (type == DEAD)
		printf(RED "| %-6ld | %d | is dead        | 💀 | \n" RESET, time, id);
	printf("------------------------------------\n");
	fflush(stdout);
	if (type != DEAD)
		sem_post(print);
}
