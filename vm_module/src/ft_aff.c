/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:31:38 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:31:43 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors				ft_aff(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			ret;

	(void)core;
	params = process->params;
	if ((ret = ft_reg(process, &p1, NULL, NULL)) != ok)
		return (ok);
	if (core->aff)
		ft_printf("Aff: %c\n", process->regs[params.p1 - 1] % 256);
	return (ok);
}
