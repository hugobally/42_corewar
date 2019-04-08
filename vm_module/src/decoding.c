#include "corewar.h"

int					ft_type_param(unsigned char bytecode, int p)
{
	unsigned char mask;
	unsigned char tmp_byte;
	int p_tmp;

	ft_printf("ft_type_param IN\n");
	p_tmp = p;
	mask = 192;
	while (p > 1)
	{
		mask = mask >> 2;
		p--;
		ft_printf("p: %d, mask: %d\n", p, mask);
	}
	p = p_tmp;
	tmp_byte = mask & bytecode;
	if (p == 1)
		tmp_byte = tmp_byte >> 6;
	else if (p == 2)
		tmp_byte = tmp_byte >> 4;
	else if (p == 3)
		tmp_byte = tmp_byte >> 2;
	ft_printf("ft_type_param OUT : tmp_byte :%d\n", tmp_byte);
	return ((int)tmp_byte);
}
