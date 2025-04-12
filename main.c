/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:46:55 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/11 22:47:02 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	start_monitor(&data);
	cleanup_resources(&data);
	return (0);
}
