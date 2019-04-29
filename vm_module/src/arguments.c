/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:28:56 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 14:30:59 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_total_size(t_core *core)
{
	t_player	*player;
	int			size;

	size = 0;
	player = core->players;
	while (player)
	{
		size += player->head.prog_size;
		player = player->next;
	}
	return (size);
}

int			ft_nb_len(long nb)
{
	int		len;
	long	tmp;

	tmp = nb;
	len = 1;
	if (nb < 0)
	{
		len++;
		nb = -nb;
		tmp = nb;
	}
	while (tmp > 9)
	{
		tmp = tmp / 10;
		len++;
	}
	return (len);
}

t_errors	ft_right_nb(char *s, t_core *core, int flag)
{
	int		len;
	int		nb_len;
	long	nb;

	len = ft_strlen(s);
	nb = (long)ft_atoi(s);
	nb_len = ft_nb_len(nb);
	if (len != nb_len || (nb < 0 && flag == 0))
		return (badarg);
	if (flag == 0)
		core->dump = nb;
	if (flag == 1)
		core->next_player = nb;
	if (flag == 2)
		core->sdump = nb;
	if (flag == 3)
		core->verbose = nb;
	return (ok);
}

t_errors	check_option(t_core *core, char **av, int *i, int ac)
{
	t_errors	ret;

	ret = badarg;
	if ((*i + 1) < ac && !ft_strcmp(av[*i], "-n"))
	{
		ret = ft_right_nb(av[++*i], core, 1);
		return (ret);
	}
	if ((*i + 1) < ac && !ft_strcmp(av[*i], "-dump"))
	{
		core->flags |= FLAG_DUMP;
		ret = ft_right_nb(av[++*i], core, 0);
		return (ret);
	}
	if ((*i + 1) < ac && !ft_strcmp(av[*i], "-d"))
	{
		core->flags |= FLAG_DUMP + FLAG_DUMP64;
		ret = ft_right_nb(av[++*i], core, 0);
		return (ret);
	}
	ret = check_option_adj(core, av, i, ac);
	return (ret);
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
			if (check_option(core, av, &i, ac) != ok)
				return (badarg);
		}
		else
		{
			core->bad_arg = av[i];
			if ((ret = new_player(core, av[i])) != ok)
				return (ret);
			++core->nb_players;
		}
		if (core->nb_players > MAX_PLAYERS)
			return (badarg);
	}
	if (ft_total_size(core) > MEM_SIZE)
		return (badchamp);
	ft_if_visu(core);
	return (core->nb_players > 0 ? ok : badarg);
}
