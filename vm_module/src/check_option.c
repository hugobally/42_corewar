/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:29:06 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:29:18 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_errors	check_option_vis(t_core *core, char **av, int *i)
{
	t_errors ret;

	ret = badarg;
	if (!ft_strcmp(av[*i], "-visu"))
	{
		core->visu = true;
		ret = ok;
	}
	if (!ft_strcmp(av[*i], "-a"))
	{
		core->aff = true;
		ret = ok;
	}
	return (ret);
}

t_errors	check_option_adj(t_core *core, char **av, int *i, int ac)
{
	t_errors ret;

	ret = badarg;
	if ((*i + 1) < ac && (!ft_strcmp(av[*i], "-sdump")
	|| !ft_strcmp(av[*i], "-s")))
	{
		core->flags |= FLAG_SDUMP;
		ret = ft_right_nb(av[++*i], core, 2);
		return (ret);
	}
	if ((*i + 1) < ac && (!ft_strcmp(av[*i], "-v")))
	{
		ret = ft_right_nb(av[++*i], core, 3);
		return (ret);
	}
	ret = check_option_vis(core, av, i);
	return (ret);
}

void		ft_if_visu(t_core *core)
{
	if (core->visu)
	{
		core->verbose = 0;
		core->dump = 0;
		core->sdump = 0;
		core->aff = 0;
		core->flags = 0;
	}
}
