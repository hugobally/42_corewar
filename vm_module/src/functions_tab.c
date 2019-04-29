/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:34:47 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:34:48 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_inst_tab			g_op_inst_tab[17] =
{
	&ft_error,
	&ft_live,
	&ft_load,
	&ft_store,
	&ft_add,
	&ft_sub,
	&ft_and,
	&ft_or,
	&ft_xor,
	&ft_zjmp,
	&ft_ldi,
	&ft_sti,
	&ft_fork,
	&ft_lld,
	&ft_lldi,
	&ft_lfork,
	&ft_aff
};
