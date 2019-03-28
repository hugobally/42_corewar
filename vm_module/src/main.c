#include "corewar.h"

void	leave(t_core *core, t_errors ret)
{
	if (core->arena)
		ft_memdel((void**)core->arena);
	if (core->process)
		del_process(core);
	if (core->players)
		del_process(core);
	print_error(ret);
	exit(0);
}

int		main(int ac, char **av)
{
    t_core		core;
	t_errors	ret;
	ft_bzero(&core, sizeof(t_core));
	if ((ret = get_arguments(&core, ac, av)))
		leave(&core, ret);
	if ((ret = make_arena(&core)))
		leave(&core, ret);
	return (0);
}
