#include "corewar.h"

int			ft_total_size(t_core *core)
{
	t_player *player;
	int size;

	size = 0;
	player = core->players;
	while (player)
	{
		size += player->head.prog_size;
		player = player->next;
	}
	return (size);
}

int 		ft_nb_len(int nb)
{
	int len;
	int tmp;

	tmp = nb;
	len = 1;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (tmp > 9)
	{
		tmp = tmp / 10;
		len++;
	}
	return(len);
}

t_errors	ft_right_nb(char *s, t_core *core, int flag)
{
	int len;
	int nb_len;
	int nb;

	len = ft_strlen(s);
	nb = ft_atoi(s);
	nb_len = ft_nb_len(nb);
	if (len != nb_len || (nb < 0 && flag == 0))
		return (badarg);
	if (flag == 0)
		core->dump = nb;
	if (flag == 1)
		core->next_player = nb;
	return (ok);
}

t_errors	get_arguments(t_core *core, int ac, char **av)
{
	int			i;
	t_errors	ret;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'd')
			{
				if ((ret = ft_right_nb(av[++i], core, 0)) != ok)
					return (badarg);
			}
			else if (av[i][1] == 'n')
				if ((ret = ft_right_nb(av[++i], core, 1)) != ok)
					return (badarg);
		}
		else
			if ((ret = new_player(core, av[i])) != ok)
				return (ret);
		if (core->nb_players > MAX_PLAYERS)
			return(badarg);
	}
	if (ft_total_size(core) > MEM_SIZE)
		return (badchamp);
	return (ok);
}
