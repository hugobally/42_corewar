/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:36:26 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:36:29 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_get_params(t_core *core, t_process *process, int p, int type)
{
	if (type == REG)
		return (process->regs[p - 1]);
	else if (type == DIR)
		return (p);
	else if (type == IND)
		return (read_val(core, get_pc(process->pc + (p % IDX_MOD)), 4));
	return (0);
}
