#include "../philo.h"

int	parse(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	return (0);
}
