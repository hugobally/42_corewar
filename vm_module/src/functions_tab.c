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
