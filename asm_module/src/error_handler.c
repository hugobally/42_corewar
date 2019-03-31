#include <unistd.h>
#include "libcorewar.h"
#include "macros.h"
#include "types.h"
#include "errors.h"
#include "libft.h"

//TODO Fix offset bug

uint32_t				get_offset(char *line, uint32_t pos)
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

void					print_line(t_file *file, uint32_t pos)
{
	char				*line;
	uint32_t			line_num;

	lseek(file->fd, 0, SEEK_SET);
	line_num = 1;
	while (get_next_line(file->fd, &line) > 0)
	{
		if (line && line_num == (pos & LINE_MASK))
		{
			ft_printf("%s\n%s%*c%s\n",
						line, GRN, get_offset(line, pos), '^', RESET);
			ft_memdel((void**)&line);
			get_next_line(-1, 0);
			break ;
		}
		ft_memdel((void**)&line);
		line_num++;
	}
}

void					print_error(char *error, uint8_t has_pos,
										uint32_t pos, t_file *file)
{
	ft_printf("%s%s:", WHT, file->name);
	if (has_pos)
		ft_printf("%d:%d: ", pos & LINE_MASK, (pos & COL_MASK) >> 16);
	ft_printf("%serror: %s%s%s\n", RED, WHT, error, RESET);
	if (has_pos)
		print_line(file, pos);
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
			ft_memdel((void**)&buffer);
		}
		i++;
	}
}

void					error_lexer(t_errors err, t_token *token, t_file *file)
{
	static t_errstr		tab[7] = {
		{label_badchar, "Forbidden char in label", 0, 0, 0},
		{label_badformat, "Bad formatting around symbol ':'", 0, 0, 0},
		{dir_badformat, "Bad formatting around symbol '%'", 0, 0, 0},
		{reg_badvalue, "Bad register [1 -", 1, REG_NUMBER, "]"},
		{cmd_unknown, "Unknown command", 0, 0, 0},
		{unknown_token, "Invalid token", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	build_errstr_tok(err, token, tab, file);
}

//void					error_parser(t_errors err, t_toktype *token);

void					error_critical(t_errors err, t_file *file)
{
	static t_errstr		tab[6] = {
		{malloc, "Malloc", 0, 0, 0},
		{open_error, "File could not be opened", 0, 0, 0},
		{read_crash, "Read Failure", 0, 0, 0},
		{read_linesize, "Line too big (Max", 1, GNL_MAX_LINE_LEN, "b)"},
		{filesize, "Input file too big (Max", 1, MAX_INPUT_FILE_SIZE, "b)"},
		{0, 0, 0, 0, 0}
	};
	build_errstr_notok(err, tab, file);
}

t_code			error_handler(t_errors code, t_token *token, t_file *file)
{
	static int		error_count;
	static t_file	*current_file;

	if (file)
	{
		current_file = file;
		return (done);
	}
	if (code < critical_error)
		error_critical(code, current_file);
	else if (code < lexer_error)
		error_lexer(code, token, current_file);
//	else if (code < parser_error)
//		error_parser(code, token, current_file);
	else
		ft_printf("Unknown Error\n");
	if (code == query && !error_count)
		return (done);
	error_count++;
	return (error);
}
