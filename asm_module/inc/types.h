/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:48:01 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:49:34 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include "macros.h"
# include "libcorewar.h"

/*
** Tokens
*/

typedef enum		e_toktype
{
	char_dir = DIRECT_CHAR,
	char_label = LABEL_CHAR,
	char_sep = SEPARATOR_CHAR,
	char_eol = EOL_CHAR,
	quote = QUOTE_CHAR,
	cmd = 0xFFFF,
	cmd_name,
	cmd_comment,
	unknown,
	label,
	opcode,
	reg,
	dir_num,
	ind_num,
	dir_label,
	ind_label
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
	t_token			*now;
	t_token			*prog_start;
	uint32_t		label_counter;
	uint32_t		byte_size;
}					t_tokenlst;

/*
** Label Table
*/

typedef struct		s_label
{
	t_token			*token;
	int32_t			offset;
}					t_label;

/*
** File Information Container
*/

typedef struct		s_file
{
	char			*name;
	int				fd;
	char			*out_name;
	int				out_fd;
}					t_file;

/*
** Line Information Container
*/

typedef struct		s_line
{
	char			*str;
	uint16_t		num;
	uint16_t		index;
	uint8_t			is_quote;
}					t_line;

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
