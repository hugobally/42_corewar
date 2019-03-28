/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:56:40 by hbally            #+#    #+#             */
/*   Updated: 2019/03/28 19:26:48 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
** Special characters not defined in op.h
*/

# define QUOTE_CHAR '"'

/*
** Padding Flags
*/

# define PAD_RIGHT 1
# define PAD_LEFT 2

/*
** Exit codes
*/

typedef enum		e_code
{
	done,
	error
}					t_code;

typedef enum		e_errors
{
	malloc,
	read,
	no_error
}					t_errors;

/*
** Tokens
*/

typedef enum		e_toktype
{
	string,
	opcode,
	reg,
	number,
	comment, 
	dir_c,
	label_c,
	separator_c,
	quote_c,
	eol_c,
	namecmd_s,
	commentcmd_s,
}					t_toktype;

typedef struct		s_token
{
	char			*value;
	t_toktype		type;
	uint64_t		pos;
	uint8_t			pad;
	struct s_token	*next;
}					t_token;

typedef struct		s_tokenlst
{
	t_token			*start;
	t_token			*end;
}					t_tokenlst;


/*
** Parsing Dispatcher __UNUSED__ ?
*/

typedef struct		s_dispatch
{
	char			character;
	t_code			(*handler)(static char*, uint64_t, int16_t*, t_tokenlst*);
}					t_dispatch;

#endif
