#include <unistd.h>
#include "libft.h"
#include "errors.h"
#include "types.h"
#include "macros.h"

//TODO Fix offset bug

static uint32_t			get_offset(char *line, uint32_t pos)
{
	uint32_t			i;
	uint32_t			offset;
	
	i = 0;
	offset = 0;
	pos = (pos & COL_MASK) >> 16;
	while (pos && line[i])
	{
		if (line[i] == '\t')
			offset += 7;
		else
			offset++;
		pos--;
		i++;
	}
	return (offset);
}

static void				print_line(t_file *file, uint32_t pos)
{
	char				*line;
	uint32_t			line_num;

	lseek(file->fd, 0, SEEK_SET);
	line_num = 1;
	while (get_next_line(file->fd, &line) > 0)
	{
		if (line_num == (pos & LINE_MASK))
		{
			ft_printf("%s\n%s%*s%s\n", line, GRN, get_offset(line, pos),
										"", RESET);
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
	if (error)
	{
		ft_printf("%s%s:", WHT, file->name);
		if (has_pos)
			ft_printf("%d:%d: ", pos & LINE_MASK, (pos & COL_MASK) >> 16);
		else
			ft_printf(" ");
		ft_printf("%serror: %s%s%s\n", RED, WHT, error, RESET);
		if (has_pos)
			print_line(file, pos);
	}
}

/*
** Build Error String
*/

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
