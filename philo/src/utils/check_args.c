/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 09:40:29 by lalhindi          #+#    #+#             */
/*   Updated: 2025-04-26 09:40:29 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (print_message(p, FORK, BLUE, "🍴"))
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_lock(p->right_fork);
	if (print_message(p, FORK, BLUE, "🍴"))
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	return (0);
}

int	odd_philo(t_philo *p)
{
	precise_usleep(1, p);
	pthread_mutex_lock(p->right_fork);
	if (print_message(p, FORK, BLUE, "🍴"))
	{
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	pthread_mutex_lock(p->left_fork);
	if (print_message(p, FORK, BLUE, "🍴"))
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;

	if (check_len(str))
		return (-2);
	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 2147483647)
		return (-2);
	return (res * sign);
}

static int	check_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!check_numeric(argv[i]))
		{
			ft_print_error("Error: Non-numeric argument : ");
			ft_print_error(argv[i]);
			write(2, "\n", 1);
			return (1);
		}
	}
	return (0);
}
