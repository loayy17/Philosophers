/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21                               #+#    #+#             */
/*   Updated: 2025/04/21                               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

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

static int check_numeric(const char *s)
{
	int i = 0;
	if (s[i] == '+') i++;
	if (!s[i]) return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int validate_args(int argc, char **argv)
{
	int i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	for (i = 1; i < argc; i++)
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
