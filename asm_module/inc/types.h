#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include "macros.h"
# include "libcorewar.h"

/*
** File Information Container
*/

typedef struct		s_file
{
	char			*name;
	int				fd;
}					t_file;

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
	//CHAR literal values are for debug only
	//Assign big values to make sure there's no overlap
	cmd = 'C',
	cmd_name = 'C',
	cmd_comment = 'C',
	unknown = 'U',
	label = 'L',
	opcode = 'O',
	reg = 'R',
	dir_num = 'D',
	ind_num = 'I',
	dir_label = 'D',
	ind_label = 'I',
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
}					t_tokenlst;

/*
** Control Flow Enums
*/

typedef enum		e_code
{
	done,
	error
}					t_code;

/*
** Dispatcher Table
*/

typedef struct		s_dispatch
{
	t_toktype		type;
	t_code			(*handler)(t_toktype, t_line*, t_tokenlst*);
}					t_dispatch;

#endif
