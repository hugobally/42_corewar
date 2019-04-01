#include "corewar.h"

void		get_params(t_core *core, t_process *pro)
{

}

void		read_instructions(t_core *core, t_process *pro)
{
	uint32_t	i;

	ft_bzero(pro->params, sizeof(t_params));
	pro->instruction_size = 1;
	i = pro->pc;
	pro->instruction = core->arena[get_pc(i)] > 16 ? 0 : core->arena[get_pc(i)];
	++i;
	if (g_op_tab[pro->instruction - 1].has_ocp)
	{
		pro->bytecode = core->arena[i++];
		++pro->instruction_size;
		get_params(core, pro);
	}
	else
	{
		pro->params.p1 = (int32_t)core->arena[get_pc(i)];
		pro->instruction_size += DIR_SIZE;
	}
}
