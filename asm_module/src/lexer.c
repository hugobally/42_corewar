#include "asm.h"
#include "types.h"
#include "errors.h"

/*
** Lexer Pass 2 : - Assign a type to all unknown tokens
**				  - Remove '%' and ':' tokens (no need for them anymore)
*/

void				tokens_foreach(t_tokenlst *lst, void (*action)(t_token*))
{
	t_token			*node;

	node = lst->start;
	while (node)
	{
		action(node);
		node = node->next;
	}
}

t_code				lexer(t_tokenlst *lst, t_file *file)
{
	tokens_foreach(lst, &find_labels);
	tokens_foreach(lst, &find_opcodes);
	tokens_foreach(lst, &find_registers);
	tokens_foreach(lst, &find_commands);
	tokens_foreach(lst, &find_num);
	if (tokens_clear(lst) == error)
		return (error);
	else
		return (syntax(lst, file));
}
