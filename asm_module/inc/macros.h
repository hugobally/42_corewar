/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:11:45 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 11:03:10 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
** Special characters not defined in op.h
*/

# define QUOTE_CHAR 			'"'
# define EOL_CHAR 				'\n'

/*
** Allowed characters in numerical value
*/

# define NUMERIC_CHARS			"-0123456789"
/*
** Padding Flags
*/

# define PAD_RIGHT 				1
# define PAD_LEFT 				2

/*
** Size Restrictions
** (Max is 10000 lines at 80 tokens / line without comments, max token length 512)
*/

# define MAX_TOKEN_STR_SIZE		512
# define MAX_TOKEN_LIST_SIZE 	10000 * 80
# define MAX_INPUT_FILE_SIZE	MAX_TOKEN_STR_SIZE * MAX_TOKEN_LIST_SIZE

#endif
