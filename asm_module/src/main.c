/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:57:01 by hbally            #+#    #+#             */
/*   Updated: 2019/04/24 16:37:08 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "asm.h"

t_code				check_filename(char *name)
{
	size_t			len;

	len = ft_strlen(name);
	if (len < 2)
		return (error);
	if (name[len - 1] != 's' || name[len - 2] != '.')
		return (error);
	return (done);
}

t_code				compile_file(t_file *file)
{
	error_handler(no_error, 0, file);
	if (check_filename(file->name) == error)
		return (error_handler(bad_filename, 0, 0));
	else
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
			return (error_handler(open_error, 0, 0));
		else
		{
			scanner(file);
			if (file->out_name)
				ft_memdel((void**)&(file->out_name));
			close(file->fd);
		}
	}
	return (done);
}

static int32_t		print_usage(void)
{
	ft_printf("\n%sUsage : ./asm [-d] [list of files]\n\n", WHT);
	ft_printf("-d : Deassemble .cor source to .s destination%s\n\n", RESET);
	return (0);
}

static int32_t		startup(int argc, char **argv, uint8_t *deasm_opt)
{
	if (argc == 1)
		return (print_usage());
	else if (!ft_strcmp(argv[1], "-d"))
	{
		if (argc == 2)
			return (print_usage());
		*deasm_opt = 1;
		return (2);
	}
	else
		return (1);
}

int					main(int argc, char **argv)
{
	int32_t			argnum;
	t_file			file;
	static uint8_t	deasm_opt;

	argnum = startup(argc, argv, &deasm_opt);
	while (argnum && argnum < argc)
	{
		ft_bzero(&file, sizeof(t_file));
		file.name = argv[argnum];
		!deasm_opt ? compile_file(&file) : deasm(&file);
		argnum++;
	}
	return (0);
}
