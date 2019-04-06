#include "libft.h"
#include "types.h"
#include "errors.h"
#include "libcorewar.h"
#include "asm.h"

t_op				*find_op(char *string)
{
	uint8_t			index;

	index = 0;
	while (g_op_tab[index].name)
	{
		if (!ft_strcmp(string, g_op_tab[index].name))
			return (&(g_op_tab[index]));
		index++;
	}
	return (NULL);
}

void				find_opcodes(t_token *token)
{
	if (token->type == unknown && find_op(token->value))
		token->type = opcode;
}

void				find_registers(t_token *token)
{
	int				reg_number;

	if (token->type == unknown && token->value[0] == 'r')
	{
		token->type = reg;
		reg_number = ft_atoi(&(token->value[1]));
		if (!ft_isnumstring(&(token->value[1]), reg_number)
				|| reg_number < 1
				|| reg_number > REG_NUMBER
				|| reg_number > 255)
		{
			error_handler(reg_badvalue, token, 0);
		}
	}
}

void				find_commands(t_token *token)
{
	if (token->type == unknown && token->value[0] == '.')
	{
		if (!ft_strcmp(token->value, NAME_CMD_STRING))
			token->type = cmd_name;
		else if (!ft_strcmp(token->value, COMMENT_CMD_STRING))
			token->type = cmd_comment;
		else
		{
			token->type = cmd;
			error_handler(cmd_unknown, token, 0);
		}
	}
}

void				find_num(t_token *token)
{
	int				i;

	if (token->type == unknown)
	{
		i = token->value[0] != '-' ? 0 : 1;
		if (!ft_isdigit(token->value[i]))
			error_handler(unknown_token, token, 0);
		else
		{
			while (ft_isdigit(token->value[i]))
				i++;
			if (token->value[i])
				error_handler(unknown_token, token, 0);
		}
		if (token->previous && token->previous->type == char_dir)
			token->type = dir_num;
		else
			token->type = ind_num;
	}
}
