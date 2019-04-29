/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:52:08 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 16:01:43 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "errors.h"
#include "types.h"
#include "macros.h"

static void				print_offset(char *line, uint32_t pos, int fd)
{
	uint32_t			i;

	i = 0;
	pos = (pos & COL_MASK) >> 16;
	while (line[i] && i < pos - 1)
	{
		ft_dprintf(fd, "%s", line[i] == '\t' ? "\t" : " ");
		i++;
	}
}

static void				print_line(t_file *file, uint32_t pos, int fd)
{
	char				*line;
	uint32_t			line_num;

	lseek(file->fd, 0, SEEK_SET);
	line_num = 1;
	while (get_next_line(file->fd, &line) > 0)
	{
		if (line_num == (pos & LINE_MASK))
		{
			ft_dprintf(fd, "%s\n", line);
			print_offset(line, pos, fd);
			ft_dprintf(fd, "%s^\n%s", RED, RESET);
			ft_memdel((void**)&line);
			break ;
		}
		ft_memdel((void**)&line);
		line_num++;
	}
	get_next_line(-1, 0);
}

void					print_error(char *error, uint8_t has_pos,
										uint32_t pos, t_file *file)
{
	int					fd;

	if (error)
	{
		fd = error[0] == '/' ? 1 : 2;
		ft_dprintf(fd, "%s%s:", WHT, file->name);
		if (has_pos)
			ft_dprintf(fd, "%d:%d: ", pos & LINE_MASK, (pos & COL_MASK) >> 16);
		else
			ft_dprintf(fd, " ");
		if (fd == 1)
			ft_dprintf(fd, "%swarning: %s%s%s\n", MAG, WHT, &(error[1]), RESET);
		else
			ft_dprintf(fd, "%serror: %s%s%s\n", RED, WHT, error, RESET);
		if (has_pos)
			print_line(file, pos, fd);
	}
}

void					build_errstr_tok(t_errors error, t_token *token,
											t_errstr *tab, t_file *file)
{
	int					i;
	char				*buffer;

	i = 0;
	while (tab[i].str1)
	{
		if (error == tab[i].errcode)
		{
			if (tab[i].has_extra)
				ft_asprintf(&buffer, "%s %d%s '%s'", tab[i].str1,
								tab[i].num_value, tab[i].str2, token->value);
			else if (token->value)
				ft_asprintf(&buffer, "%s '%s'", tab[i].str1, token->value);
			else
				ft_asprintf(&buffer, "%s", tab[i].str1);
			print_error(buffer, 1, token->pos, file);
			if (buffer)
				ft_memdel((void**)&buffer);
		}
		i++;
	}
}

void					build_errstr_notok(t_errors error, t_errstr *tab,
											t_file *file)
{
	int					i;
	char				*buffer;

	i = 0;
	while (tab[i].str1)
	{
		if (error == tab[i].errcode)
		{
			if (tab[i].has_extra)
				ft_asprintf(&buffer, "%s %d %s", tab[i].str1,
								tab[i].num_value, tab[i].str2);
			else
				ft_asprintf(&buffer, "%s", tab[i].str1);
			print_error(buffer, 0, 0, file);
			if (buffer)
				ft_memdel((void**)&buffer);
		}
		i++;
	}
}
