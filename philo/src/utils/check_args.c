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

/* ensure string is all digits (allow leading '+') */
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
			write(2, "Error: Non-numeric argument: ", 29);
			write(2, argv[i], strlen(argv[i]));
			write(2, "\n", 1);
			return (1);
		}
	}
	return (0);
}
