/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:46:14 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:47:41 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Special characters not defined in op.h
*/

# define QUOTE_CHAR 			'"'
# define EOL_CHAR 				'\n'
# define COMMENT_CHAR_2			';'

/*
** Padding Flags
*/

# define PAD_RIGHT 				1
# define PAD_LEFT 				2

# define END_QUOTE				1
# define NO_END_QUOTE			0

/*
** Masks to extract line and column from int64 during error reporting
*/

# define LINE_MASK 0x0000FFFF
# define COL_MASK 0xFFFF0000

/*
** Size Restrictions
*/

# define MAX_TOKEN_STR_SIZE		512
# define MAX_INPUT_FILE_SIZE	10000000
# define MAX_OUTPUT_BYTE_SIZE	32767

/*
** Misc Code Clarity
*/

# define DUMMY_WRITE NULL

#endif
