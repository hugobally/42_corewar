#include "libft.h"
#include "types.h"
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
		token->type = value_reg;
		reg_number = ft_atoi(&(token->value[1]));
		if (!ft_isnumstring(&(token->value[1]), reg_number)
				|| reg_number < 1 || reg_number > REG_NUMBER
				|| reg_number > 255)
		{//
			ft_printf("bad value on reg value line %d\n", token->pos & 0x0000FFFF);//debug
			error_handler(value_reg_badvalue, token, 0);
		}//
	}
}

void				find_commands(t_token *token)
{
	if (token->type == unknown && token->value[0] == '.')
	{
		if (!ft_strcmp(token->value, NAME_CMD_STRING))
			token->type = cmd_name;
		if (!ft_strcmp(token->value, COMMENT_CMD_STRING))
			token->type = cmd_comment;
	}
}

void				find_values(t_token *token)
{
	int				number;
	int				i;

	if (token->type == unknown)
	{
		i = 0;
		while (token->value[i] == '0' && token->value[i + 1])
			i++;
		number = ft_atoi(&(token->value[i]));
		if (!ft_isnumstring(&(token->value[i]), number))
		{//
			ft_printf("line %d col %d : invalid token '%s'\n", token->pos & 0x0000FFFF, (token->pos & 0xFFFF0000) >> 16, token->value);//
			error_handler(unknown_token, token, 0);
		}//
		else
			token->type = value_num;
	}
}
