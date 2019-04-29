/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:37:55 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:37:56 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors				ft_error(t_core *core, t_process *process)
{
	(void)core;
	(void)process;
	return (ok);
}

t_errors				ft_reg(t_process *p, int *p1, int *p2, int *p3)
{
	if (p1)
		*p1 = ft_type_param(p->params.bytecode, 1);
	if (p2)
		*p2 = ft_type_param(p->params.bytecode, 2);
	if (p3)
		*p3 = ft_type_param(p->params.bytecode, 3);
	if (p1 && *p1 == REG)
		if (p->params.p1 <= 0 || p->params.p1 > REG_NUMBER)
			return (1);
	if (p2 && *p2 == REG)
		if (p->params.p2 <= 0 || p->params.p2 > REG_NUMBER)
			return (1);
	if (p3 && *p3 == REG)
		if (p->params.p3 <= 0 || p->params.p3 > REG_NUMBER)
			return (1);
	return (ok);
}
