#include "types.h"
#include "asm.h"

#include "libft.h"//DEBUG

/*
** Lexer -> Pass 2 - IDENTIFIER : Determine what each unknown token is
**								  and identify errors
*/

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

t_code			lexer_checker(t_tokenlst *lst)
{
	tokens_foreach(lst, &find_labels_pass1);
	tokens_foreach(lst, &find_labels_pass2);
	tokens_foreach(lst, &find_opcodes);
	tokens_foreach(lst, &find_registers);
	tokens_foreach(lst, &find_commands);
	tokens_foreach(lst, &find_values);
	debug_printtokenlst(lst);
	return (done);
}
