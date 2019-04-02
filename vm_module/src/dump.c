#include "corewar.h"

void	printx(unsigned char c)
{
	unsigned char	p;

	p = (c / 16) + ((c / 16) < 10 ? '0' : 'a' - 10);
	ft_putchar(p);
	p = (c % 16) + ((c % 16) < 10 ? '0' : 'a' - 10);
	ft_putchar(p);
}

void	hexdump(t_core *core)
{
	int	i;
	int	col;

	i = -1;
	while (i < MEM_SIZE)
	{
		col = -1;
		while (++col < 32)
		{
			printx(core->arena[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
