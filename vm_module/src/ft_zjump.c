/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:34:32 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:34:33 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "graph.h"

t_errors		ft_zjmp(t_core *core, t_process *process)
{
	if (core->verbose & 4)
		ft_printf("P%5d | zjmp %d %s\n", process->pro_name,
		process->params.p1, process->carry ? "OK" : "FAILED");
	(void)core;
	if (process->carry == true)
	{
		if (core->visu)
		{
			move_proccess_on_arena(process->pc,
			process->pc + process->params.p1, core);
		}
		process->pc = get_pc(process->pc + process->params.p1 % IDX_MOD);
	}
	return (ok);
}
