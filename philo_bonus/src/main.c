/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:04:03 by lalhindi          #+#    #+#             */
/*   Updated: 2025/04/03 18:16:26 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	memset(&data, 0, sizeof(t_data));
	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	start_monitor(&data);
	i = -1;
	while (++i < data.n_philos)
		waitpid(data.philo[i].pid, NULL, 0);
	cleanup_resources(&data);
	return (0);
}
