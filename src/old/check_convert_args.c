/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_convert_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:09:10 by lalhindi          #+#    #+#             */
/*   Updated: 2025/03/15 01:09:54 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	return (0);
}

int	validate_args_values(int argc, char **argv)
{
	int	i;
	int	is_digit;

	i = 0;
	while (++i < argc)
	{
		is_digit = ft_isdigit(argv[i]);
		if (is_digit == 0)
		{
			printf("Error: Invalid argument %s\n", argv[i]);
			return (1);
		}
		if (is_digit == 2)
		{
			printf("Error: Found Negative Sign %s\n", argv[i]);
			return (1);
		}
	}
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if (validate_number_of_args(argc))
		return (1);
	if (validate_args_values(argc, argv))
		return (1);
	return (0);
}

int	validate_data_value(t_data *data)
{
	if (data->n_philos <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0 || (data->n_must_eat != -1
			&& data->n_must_eat < 1))
	{
		printf("Error: Invalid values of arguments\n");
		return (1);
	}
	return (0);
}
