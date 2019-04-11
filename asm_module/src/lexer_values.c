#include "libft.h"
#include "types.h"
#include "errors.h"
#include "libcorewar.h"
#include "asm.h"

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

uint8_t				check_hex_value(t_token *token)
{
	int				i;

	i = 2;
	if (token->value[0] == '0' && token->value[1]
			&& ft_strchr("xX", token->value[1]))
	{
		while (token->value[i]
				&& ft_strchr("0123456789AaBbCcDdEeFf", token->value[i]))
			i++;
		if (i == 2 || token->value[i])
			error_handler(unknown_token, token, 0);
		return (1);
	}
	else 
		return (0);
}

void				find_num(t_token *token)
{
	int				i;

	if (token->type == unknown)
	{
		if (token->previous && token->previous->type == char_dir)
			token->type = dir_num;
		else
			token->type = ind_num;
		if (!check_hex_value(token))
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
		}
	}
}
