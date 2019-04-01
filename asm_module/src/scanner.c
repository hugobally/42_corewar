#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

///////////////////////////////////////////////////////////////

void			debug_printtokenlst(t_tokenlst *lst)
{
	t_token *node;
	node = lst->start;
	while (node)
	{
		ft_printf("%30s | %c | pos %03d-%03d | pad %3d\n", \
				node->value ? node->value : \
					node->type != '\n' ? (char*)(&(node->type)) : "EOL", \
				(char)(node->type) != '\n' ? (char)(node->type) : '\\', \
				node->pos & 0x0000FFFFu, \
				(node->pos & 0xFFFF0000u) >> 16, \
				node->pad);
		node = node->next;
	}
}
///////////////////////////////////////////////////////////////

/*
** Lexer -> Pass 1 - SCANNER : Acquire all the tokens, either as
** 					1) special single char
**					2) anything else in between
**				  Comments and whitespace are discarded
**				  We store info about whitespace inside each token
*/

///////////////////////////////////////////////////////////////

static t_code			dispatcher(t_line *line, t_tokenlst *lst)
{
	uint16_t			j;
	static t_dispatch	tab[4] = {
		{char_label, &token_single},
		{char_dir, &token_single},
		{char_sep, &token_single},
		{quote, &token_quote},
	};

	j = 0;
	while (j < 4)
	{
		if (line->str[line->index] == (char)(tab[j].type))
			return (tab[j].handler(tab[j].type, line, lst));
		j++;
	}
	return (token_unknown_wrapper(unknown, line, lst));
}

static t_code			process_line(t_line *line, t_tokenlst *lst)
{
	t_code				ret_code;

	line->index = 0;
	while (line->str[line->index])
		if ((ret_code = dispatcher(line, lst)) == error)
			break ;
	if (ret_code == done && !(lst->end && lst->end->type == char_eol))
		ret_code = token_single(char_eol, line, lst);
	ft_memdel((void**)&(line->str));
	return (ret_code);
}

t_code					scanner(const t_file *file)
{
	int32_t				ret;
	t_line				line;
	t_tokenlst			lst;

	ft_bzero(&lst, sizeof(t_tokenlst));
	ft_bzero(&line, sizeof(t_line));
	while ((ret = get_next_line(file->fd, &(line.str))) > 0)
	{
		line.num++;
		if (line.str[0] && process_line(&line, &lst) == error)
			return (scanner_exit(&lst, err));
	}
	if (ret < 0)
		return (scanner_exit(&lst, ret));
	return (scanner_exit(&lst, lexer(&lst, file) == done ? no_err : err));
			//gnl avec -1 et null pour clean le static dans lexer exit
}
