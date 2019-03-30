/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:56:40 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 11:15:13 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include "macros.h"
# include "libcorewar.h"

/*
** Line Information Container
*/

typedef struct		s_line
{
	char			*str;
	uint16_t		num;
	uint16_t		index;
}					t_line;
/*
** Tokens
*/

typedef enum		e_toktype
{
	cmd = 'C',
	value_string = 'S',
	value_label = 'L',
	value_opcode = 'O',
	value_reg = 'R',
	value_number = 'N',
	char_dir = DIRECT_CHAR,
	char_label = LABEL_CHAR,
	char_sep = SEPARATOR_CHAR,
	char_eol = EOL_CHAR,
	quote = QUOTE_CHAR
}					t_toktype;

typedef struct		s_token
{
	char			*value;
	t_toktype		type;
	uint32_t		pos;
	uint8_t			pad;
	struct s_token	*next;
}					t_token;

typedef struct		s_tokenlst
{
	t_token			*start;
	t_token			*end;
	uint32_t		size;
}					t_tokenlst;

/*
** Control Flow Enums
*/

typedef enum		e_code
{
	done,
	error
}					t_code;

typedef enum		e_errors
{
	malloc,//no token
	read_crash,
	read_linesize,
	filesize,
	strsize,//no token
	quote_unterminated, //no token
	err,
	no_err
}					t_errors;

/*
** Dispatcher Table
*/

typedef struct		s_dispatch
{
	t_toktype		type;
	t_code			(*handler)(t_toktype, t_line*, t_tokenlst*);
}					t_dispatch;

#endif
