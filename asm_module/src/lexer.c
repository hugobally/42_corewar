#include "asm.h"
#include "types.h"
#include "errors.h"

///////////////////////////////////////////////////////////////

/*
** Lexer Pass 2 : - Assign a type to all unknown tokens
**				  - Remove '%' and ':' tokens (no need for them anymore)
*/

///////////////////////////////////////////////////////////////

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
			if ((node->pad & PAD_RIGHT) || !node->next
					|| (node->next->type != dir_num
						&& node->next->type != char_label))
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

t_code			check_empty(t_tokenlst *lst)
{
	if (lst->start && lst->start->type == char_eol)
		token_del(lst->start, lst);
	if (!lst->start)
		return (error_handler(no_instructions, 0, 0));
	return (done);
}

t_code			lexer(t_tokenlst *lst, const t_file *file)
{
	tokens_foreach(lst, &find_labels);
	tokens_foreach(lst, &find_opcodes);
	tokens_foreach(lst, &find_registers);
	tokens_foreach(lst, &find_commands);
	tokens_foreach(lst, &find_num);
	tokens_clear(lst);
	if (check_empty(lst) == error)
		return (error);
	return (syntax(lst, file));
}
