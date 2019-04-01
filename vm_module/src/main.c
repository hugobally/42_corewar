#include "corewar.h"
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
	(void)ret;
	ft_printf("Error\n");
}

void	leave(t_core *core, t_errors ret)
{
	if (core->process)
		del_process(core);
	if (core->players)
		del_players(core);
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
	if ((ret = the_game(&core) != ok))
		leave(&core, ret);
	return (0);
}
