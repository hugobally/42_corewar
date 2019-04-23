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
