#include "corewar.h"

t_errors	check_option_vis(t_core *core, char **av, int *i)
{
	t_errors ret;

	ret = badarg;
	if (!ft_strcmp(av[*i], "-visu"))
	{
		core->visu = true;
		ret = ok;
	}
	if (!ft_strcmp(av[*i], "-a"))
	{
		core->aff = true;
		ret = ok;
	}
	return (ret);
}

t_errors	check_option_adj(t_core *core, char **av, int *i, int ac)
{
	t_errors ret;

	ret = badarg;
	if ((*i + 1) < ac && (!ft_strcmp(av[*i], "-sdump")
	|| !ft_strcmp(av[*i], "-s")))
	{
		core->flags |= FLAG_SDUMP;
		ret = ft_right_nb(av[++*i], core, 2);
		return (ret);
	}
	if ((*i + 1) < ac && (!ft_strcmp(av[*i], "-v")))
	{
		ret = ft_right_nb(av[++*i], core, 3);
		return (ret);
	}
	ret = check_option_vis(core, av, i);
	return (ret);
}
