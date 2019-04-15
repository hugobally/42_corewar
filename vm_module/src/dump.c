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

void	hexdump(t_core *core)
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
		while (++col < 64)
		{
			printx(core->arena[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	if (core->sdump != 0)
		while (!read(1, NULL, 1))
			;
}
