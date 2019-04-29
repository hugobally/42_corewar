/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:06 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:30:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "unistd.h"

void	printx(unsigned char c)
{
	unsigned char	p;

	p = (c / 16) + ((c / 16) < 10 ? '0' : 'a' - 10);
	ft_putchar(p);
	p = (c % 16) + ((c % 16) < 10 ? '0' : 'a' - 10);
	ft_putchar(p);
}

int		hexdump(t_core *core, int flag)
{
	uint32_t	i;
	int			col;

	i = 0;
	while (i < MEM_SIZE)
	{
		col = -1;
		if (i == 0)
			ft_putstr("0x");
		ft_printf("%#.4x : ", i);
		while (++col < ((core->flags & FLAG_DUMP64 || flag) ? 64 : 32))
		{
			printx(core->arena[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	if (flag)
		while (!read(1, NULL, 1))
			;
	return (0);
}
