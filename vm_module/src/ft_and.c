/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:31:53 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:31:57 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors	ft_and(t_core *core, t_process *process)
{
	int			p1;
	int			p2;
	int			pa[3];

	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	p1 = ft_get_params(core, process, process->params.p1, pa[0]);
	p2 = ft_get_params(core, process, process->params.p2, pa[1]);
	process->regs[process->params.p3 - 1] = p1 & p2;
	ft_carry(process, process->regs[process->params.p3 - 1]);
	if (core->verbose & 4)
		ft_printf("P%5d | and %d %d r%d\n",
			process->pro_name,
			p1,
			p2,
			process->params.p3);
	return (ok);
}
