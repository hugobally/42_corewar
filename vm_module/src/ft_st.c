/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:33:53 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:33:54 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors		ft_store(t_core *core, t_process *process)
{
	t_params		params;
	int				p1;
	int				p2;

	params = process->params;
	if (ft_reg(process, &p1, &p2, NULL) != ok)
		return (ok);
	if (p2 == REG)
		process->regs[params.p2 - 1] = (int)process->regs[params.p1 - 1];
	else if (p2 == IND)
	{
		if (core->visu)
			core->graph->tmp_player = process->player;
		write_val(core, get_pc(process->pc + params.p2 % IDX_MOD),
		4, process->regs[params.p1 - 1]);
	}
	if (core->verbose & 4)
		ft_printf("P%5d | st r%d %d\n", process->pro_name,
		process->params.p1, process->params.p2);
	return (ok);
}
