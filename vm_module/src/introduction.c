/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:38:01 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:38:02 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduction(t_player *player)
{
	ft_putendl("Introducing contestants...");
	while (player)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		-player->p, player->head.prog_size, player->head.prog_name,
		player->head.comment);
		player = player->next;
	}
}
