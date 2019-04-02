#include "corewar.h"

void		push_process(t_core *core, t_process *new)
{
	new->next = core->process;
	core->process = new;
}

/*
** Reste a initialiser les valeurs.
*/

t_errors	make_process(t_core *core, uint32_t pc)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (falloc);
	new->pc = pc;
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
		{
			ft_printf("player->p :%d, nb :%d\n", player->p, nb);
			ft_printf("here\n");
			return (badarg);
		}
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

	nb = 0;
	player = core->players;
	start = player;
	if (core->next_player)
		return (nb_player_spec(core, new));
	while (player != NULL)
	{
		if (player->p == nb)
		{
			nb++;
			player = start;
		}
		else
			player = player->next;
	}
	new->p = nb;
	return (ok);
}
