/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:32:50 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:32:51 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors		ft_load(t_core *core, t_process *process)
{
	t_params		params;
	int				p1;
	int				p2;
	int				p3;
	int				ret;

	params = process->params;
	process->params.p3 = 1;
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	else if (p1 == IND)
		process->regs[params.p2 - 1] = read_val(core,
		get_pc(process->pc + params.p1 % IDX_MOD), 4);
	if (core->verbose & 4)
		ft_printf("P%5d | ld %d r%d\n",
			process->pro_name,
			process->regs[process->params.p2 - 1],
			process->params.p2);
	ft_carry(process, process->regs[params.p2 - 1]);
	return (ok);
}
