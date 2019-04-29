/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:34:12 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:34:13 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors	ft_sub(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;

	(void)core;
	params = process->params;
	if (ft_reg(process, &p1, &p2, &p3) != ok)
		return (ok);
	process->regs[params.p3 - 1] = process->regs[params.p1 - 1]
		- process->regs[params.p2 - 1];
	ft_carry(process, process->regs[params.p3 - 1]);
	if (core->verbose & 4)
		ft_printf("P%5d | sub r%d r%d r%d\n",
			process->pro_name,
			process->params.p1,
			process->params.p2,
			process->params.p3);
	return (ok);
}
