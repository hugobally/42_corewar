#include "types.h"
#include "libft.h"
#include "libcorewar.h"
#include "asm.h"

static void		check_label_badchar(t_token *token)
{
	uint32_t	i;

	i = 0;
	while (token->value[i])
	{
		if (!strchr(LABEL_CHARS, token->value[i]))
		{//
			ft_printf("bad chars in label name '%s' on line %d\n", token->value, token->pos & 0x0000FFFF);// debug
			error_handler(label_badchar, token, 0);
		}//
		i++;
	}
}

void			find_labels_pass1(t_token *token)
{
	if (token->type == unknown
			&& token->next && token->next->type == char_label)
	{
		token->type = label;
		check_label_badchar(token);
	}
}

void			find_labels_pass2(t_token *token)
{
	if (token->type == char_label
			&& token->next && token->next->type == unknown)
	{
		if (!(token->previous && token->previous->type == label))
		{
			token->next->type = label;
			check_label_badchar(token->next);
		}
	}
}

