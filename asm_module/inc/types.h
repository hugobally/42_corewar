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
	//CHAR values are for debug only
	cmd = 'C',
	cmd_name = 'C',
	cmd_comment = 'C',
	unknown = 'U',
	label = 'L',
	opcode = 'O',
	value_num = 'N',
	value_reg = 'R',
	value_dir = 'D',
	value_ind = 'I',
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
	struct s_token	*previous;
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
	read_linesize = -2,//no token, critical
	read_crash = -1,//no token, critical
	malloc,//no token, critical
	filesize, //no token, critical
	strsize,//no token, critical
	quote_unterminated, //no token -- no critical
	label_badchar,
	value_reg_badvalue,
//	value_num_range, // possibly unused
	cmd_unknown,
	unknown_token,
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
