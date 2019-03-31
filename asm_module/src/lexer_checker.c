#include "types.h"
#include "asm.h"

#include "libft.h"//DEBUG

/*
** Lexer -> Pass 2 - IDENTIFIER : Determine what each unknown token is
**								  and identify errors
*/

void			tokens_clear(t_tokenlst *lst)
{
	t_token		*node;
	t_token		*next;

	node = lst->start;
	while (node)
	{
		next = node->next;
		if (node->type == char_dir)
		{
			if (!(node->next)
					|| !(node->next->type == dir_num
						|| node->next->type == dir_label)
					|| (node->pad & PAD_RIGHT))
				error_handler(dir_badformat, node, 0);
			token_del(node, lst);
		}
		if (node->type == char_label)
			token_del(node, lst);
		node = next;
	}
}

void			tokens_foreach(t_tokenlst *lst, void (*action)(t_token*))
{
	t_token		*node;

	node = lst->start;
	while (node)
	{
		action(node);
		node = node->next;
	}
}

/*
** Lexer Pass 2 : - Assign a type to all unknown tokens
**				  - Remove '%' and ':' tokens (no need for them anymore)
*/

t_code			lexer_checker(t_tokenlst *lst)
{
	tokens_foreach(lst, &find_labels);
	tokens_foreach(lst, &find_opcodes);
	tokens_foreach(lst, &find_registers);
	tokens_foreach(lst, &find_commands);
	tokens_foreach(lst, &find_num);
	tokens_clear(lst);
	debug_printtokenlst(lst);
	return (done);
}
