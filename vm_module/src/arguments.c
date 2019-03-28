#include "corewar.h"

/*
** recupere les arguments, decide du placement des process.
*/

t_errors	get_arguments(t_core *core, int ac, char **av)
{
	int			i;
	t_errors	ret;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'd')
				core->dump = ft_atoi(av[++i]);
			else if (av[i][1] == 'n')
				core->next_player = ft_atoi(av[++i]);
		}
		else
			if (ret = new_player(core, av[i]) != ok)
				return (ret);
	}
	return (ok);
}
