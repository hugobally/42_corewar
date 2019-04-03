#include "types.h"
#include "errors.h"
#include "libft.h"

void			token_del(t_token *token, t_tokenlst *lst)
{
	if (token->value)
		ft_memdel((void**)&(token->value));
	if (token->previous)
		token->previous->next = token->next;
	if (token->next)
		token->next->previous = token->previous;
	if (token == lst->end)
		lst->end = token->previous;
	if (token == lst->start)
		lst->start = token->next;
	token->next = NULL;
	token->previous = NULL;
	ft_memdel((void**)&(token));
}

t_code			scanner_exit(t_tokenlst *lst, t_errors code)
{
	(void)lst;
	(void)code;
	return (done);
}
