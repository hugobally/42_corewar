/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:38:33 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:38:34 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_error(t_errors ret, char *arg, int bad_size)
{
	if (ret == falloc)
		ft_putendl_fd("Malloc failed", 2);
	else if (ret == badarg)
		ft_putendl_fd("Bad argument", 2);
	else if (ret == codesize)
	{
		ft_dprintf(2, "Error: File %s has a code size ", arg);
		ft_dprintf(2, "that differ from what its header says\n");
	}
	else if (ret == champlarge)
		ft_dprintf(2,
		"Error: File %s has too large a code (%d bytes > %d bytes)\n",
		arg, bad_size, CHAMP_MAX_SIZE);
	else if (ret == badchamp)
		ft_putendl_fd("Bad champ", 2);
	else if (ret == badfile)
		ft_putendl_fd("Bad file", 2);
	else if (ret == badopen)
		ft_dprintf(2, "Can't read source file %s\n", arg);
	else if (ret == no_color)
		ft_putendl_fd("Terminal does not support color", 2);
	else if (ret == filesmall)
		ft_dprintf(2, "Error: File %s is too small to be a champion\n", arg);
	else if (ret == badmagic)
		ft_dprintf(2, "Erorr: File %s has an invalid header\n", arg);
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
	print_error(ret, core->bad_arg, core->bad_size);
	if (ret == f1_exit)
		ft_putendl_fd("Game exit", 2);
	exit(0);
}

int		main(int ac, char **av)
{
	t_core		core;
	t_errors	ret;

	if (ft_usage(av[0], ac))
		return (0);
	ft_bzero(&core, sizeof(t_core));
	if ((ret = get_arguments(&core, ac, av)) != ok)
		leave(&core, ret);
	introduction(core.players);
	if ((ret = make_arena(&core)) != ok)
		leave(&core, ret);
	if (core.visu)
	{
		if ((ret = make_graph(&core)) != ok)
			leave(&core, ret);
		make_win(&core);
		ret = init_thread(&core);
	}
	else
	{
		core.graph = NULL;
		ret = the_game(&core);
	}
	leave(&core, ret);
	return (0);
}
