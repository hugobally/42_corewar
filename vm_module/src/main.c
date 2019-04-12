#include "corewar.h"
#include "graph.h"
#include <stdlib.h>

void	del_process(t_core *core)
{
	t_process	*tmp;
	t_process	*pro;

	pro = core->process;
	while (pro)
	{
		tmp = pro;
		pro = pro->next;
		free(tmp);
	}
}

void	del_players(t_core *core)
{
	t_player	*tmp;
	t_player	*pla;

	pla = core->players;
	while (pla)
	{
		tmp = pla;
		pla = pla->next;
		free(tmp);
	}
}

void	print_error(t_errors ret)
{
	if (ret == falloc)
		ft_putendl_fd("Malloc failed", 2);
	else if (ret == badarg)
		ft_putendl_fd("Bad argument", 2);
	else if (ret == badchamp)
		ft_putendl_fd("Bad champ", 2);
	else if (ret == badfile)
		ft_putendl_fd("Bad file", 2);
	else if (ret == badopen)
		ft_putendl_fd("Bad open", 2);
	else if (ret == no_color)
		ft_putendl_fd("Terminal does not support color", 2);
	else if (ret == f1_exit)
		ft_putendl_fd("Game exit", 2);
}

void	leave(t_core *core, t_errors ret)
{
	if (core->process)
		del_process(core);
	if (core->players)
		del_players(core);
	if (core->graph)
	{
		free_graph(core->graph);
		endwin();
	}
	print_error(ret);
	exit(0);
}

int		main(int ac, char **av)
{
    t_core		core;
	t_errors	ret;

	ft_bzero(&core, sizeof(t_core));
	if ((ret = get_arguments(&core, ac, av)) != ok)
		leave(&core, ret);
	ft_printf("Arguments done\n");
	if ((ret = make_arena(&core)) != ok)
		leave(&core, ret);
	ft_printf("Arena made\n");
	if (core.visu)
	{
		if ((ret = make_graph(&core)) != ok)
			leave(&core, ret);
		make_win(&core);
	}
	ret = the_game(&core);
	leave(&core, ret);
	return (0);
}
