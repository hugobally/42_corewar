#include "corewar.h"


int		main(int ac, char **av)
{
    t_core	core;

	ft_bzero(core, sizeof(t_core));
	if (get_arguments(&core, ac, av))
		return (0);
	return (0);
}
