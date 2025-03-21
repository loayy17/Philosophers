#include "philo.h"

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
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!check_numeric(argv[i]))
		{
			printf("Error: Non-numeric argument: %s\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
