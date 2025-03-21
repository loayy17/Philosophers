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