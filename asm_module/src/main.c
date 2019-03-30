/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:20:49 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 11:34:17 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include <fcntl.h>//move if open is moved elsewhere
#include "libft.h"//debug

int					main(int argc, char **argv)
{
	//TEMPORARY
	int fd;
	(void)argc;
	fd = open(argv[1], O_RDONLY);
	lexer_get(fd);
	//END TEMPORARY
}
