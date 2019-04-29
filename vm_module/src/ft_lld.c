/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:33:26 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 17:02:01 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors			ft_lld(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;

	params = process->params;
	if (ft_reg(process, &p1, &p2, NULL) != ok)
		return (ok);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	else if (p1 == IND)
		process->regs[params.p2 - 1] = read_val(core,
		get_pc(process->pc + params.p1), 2);
	ft_carry(process, process->regs[params.p2 - 1]);
	if (core->verbose & 4)
		ft_printf("P%5d | lld %d r%d\n", process->pro_name,
		process->regs[params.p2 - 1], process->params.p2);
	return (ok);
}
