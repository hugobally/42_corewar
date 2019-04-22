/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:51 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:58:52 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "types.h"
#include "errors.h"

t_code				syntax_exit(t_label **label_tab, t_errors error)
{
	int				i;

	i = 0;
	if (*label_tab)
	{
		while ((*label_tab)[i].token)
		{
			((*label_tab)[i].token = NULL);
			i++;
		}
		ft_memdel((void**)label_tab);
	}
	if (error == write_crash)
		error_handler(write_crash, 0, 0);
	if (error == parser_error)
		return (error);
	else
		return (done);
}
