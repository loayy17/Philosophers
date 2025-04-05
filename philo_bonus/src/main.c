/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:32:16 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/05 09:32:28 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		return_code;

	return_code = 0;
	if (validate_args(argc, argv))
		return (1);
	return_code = init_data(&data, argc, argv);
	if (return_code)
	{
		error_message(return_code);
		return (1);
	}
	if (start_simulation(&data, &return_code))
	{
		error_message(return_code);
		return (1);
	}
	cleanup(&data);
	return (0);
}
