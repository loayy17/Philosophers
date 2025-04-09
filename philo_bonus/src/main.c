#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_data	data;
	if(validate_args(ac, av))
		return (print_stderr("Error: Invalid arguments\n",1));
	if(init_data(&data,ac, av) && check_args(&data))
		return (print_stderr("Error: Initialization failed\n",1));
	start_processes(&data);
	cleanup(&data);
	return (0);	
}