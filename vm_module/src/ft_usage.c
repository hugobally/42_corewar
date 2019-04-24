/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:42:24 by rle-ru            #+#    #+#             */
/*   Updated: 2019/04/23 15:02:22 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_usage(char *exe_name, int ac)
{
	if (ac > 1)
		return (0);
	ft_printf(
	"Usage: %s [-s N -dump N -d N -v N | -visu | -a] <champion1.cor> <...>\n",
	exe_name);
	ft_printf("-visu   : Ncurses output mode\n");
	ft_printf("-a      : Prints output from \"aff\" (Default is to hide it)\n");
	ft_printf("## TEXT MODE ##\n");
	ft_printf(
	"-d      : Dumps memory after N cycles then exits. 64 bytes per line\n");
	ft_printf(
	"-dump   : Dumps memory after N cycles then exits. 32 bytes per line\n");
	ft_printf(
	"-s      : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf(
	"-sdump  : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf(
	"-v N    : Verbosity levels, can be added together to enable several\n");
	ft_printf("          - 1 : Show lives\n");
	ft_printf("          - 2 : Show cycles\n");
	ft_printf("          - 4 : Show operations\n");
	ft_printf("          - 8 : Show deaths\n");
	ft_printf("          - 16 : Show PC movements\n");
	return (1);
}
