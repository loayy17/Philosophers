/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/04/12 19:29:23 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/12 19:29:23 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_print_error("Error: Invalid number of arguments\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!check_numeric(argv[i]))
		{
			ft_print_error("Error: Non-numeric argument: ");
			ft_print_error(argv[i]);
			ft_print_error("\n");
			return (1);
		}
	}
	return (0);
}

int	check_args(t_data *data)
{
	if (data->n_philo < 1 || data->t_to_die < 0 || data->t_to_eat < 0
		|| data->t_to_sleep < 0 || (data->max_meals != -1
			&& data->max_meals < 1))
	{
		printf("%d %d %d %d %d\n", data->n_philo, data->t_to_die,
			data->t_to_eat, data->t_to_sleep, data->max_meals);
		ft_print_error("Error: Invalid argument\n");
		return (1);
	}
	return (0);
}
