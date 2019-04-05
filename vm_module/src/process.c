#include "corewar.h"

void		push_process(t_core *core, t_process *new)
{
	new->next = core->process;
	core->process = new;
}

/*
** Reste a initialiser les valeurs.
*/

t_errors	make_process(t_core *core, uint32_t pc, t_player *pl)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (falloc);
	new->pc = pc;
	new->regs[0] = pl->p;
	push_process(core, new);
	return (ok);
}

t_errors	nb_player_spec(t_core *core, t_player *new)
{
	int nb;
	t_player *player;

	player = core->players;
	nb = core->next_player;

	while (player != NULL)
	{
		if (player->p == nb)
			return (badarg);
		player = player->next;
	}
	core->next_player = 0;
	new->p = nb;
	return (ok);
}

t_errors	nb_player(t_core *core, t_player *new)
{
	int nb;
	t_player *start;
	t_player *player;

	//ft_printf("nb_player IN\n");
	nb = 0;
	player = core->players;
	start = player;
	if (core->next_player)
		return (nb_player_spec(core, new));
	//ft_printf("nb_player MID\n");
	while (player)
	{
		//ft_printf("nb_player MID_1\n");
		if (player->p == nb)
		{
			//ft_printf("nb_player MID_1.5\n");
			nb++;
			player = start;
		}
		player = player->next;
		//ft_printf("nb_player MID_2\n");
	}
	new->p = nb;
	//ft_printf("nb_player OUT\n");
	return (ok);
}
