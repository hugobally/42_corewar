#include "corewar.h"

void		add_process(t_player *pl, t_core *core, uint32_t pc)
{
	ft_memcpy(&core->arena[pc], pl->proc, pl->head.prog_size);
}

t_errors	make_arena(t_core *core)
{
	int			cur;
	t_player	*pl;
	t_errors	ret;

	cur = 0;
	pl = core->players;
	core->max_cycle_to_die = CYCLE_TO_DIE;
	core->max_checks = MAX_CHECKS;
	//ft_printf("make arena IN\n");
	while (pl)
	{
		//ft_printf("make arena MID_0\n");
		add_process(pl, core, cur);
		//ft_printf("make arena MID_0.5\n");
		if ((ret = make_process(core, cur, pl)) != ok)
			return (ret);
		//ft_printf("make arena MID\n");
		pl = pl->next;
		//ft_printf("make arena MID_1\n");
		cur += MEM_SIZE / core->nb_players;
		//ft_printf("make arena MID_2\n");
	}
	//ft_printf("make arena OUT\n");
	return (ok);
}
