/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:29:36 by hbally            #+#    #+#             */
/*   Updated: 2019/03/29 16:59:38 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "types.h"

/*
** Lexer Pass 1
*/

t_code			lexer_get(const int fd);
t_code			lexer_exit(t_tokenlst *lst, t_errors code);

/*
** Token Handling
*/


void			template_init(t_token *template, t_toktype type, t_line *line);
void			get_right_pad(t_token *template, t_line *line);
t_code			token_add(t_tokenlst *lst, const t_token *template);
t_code			token_single(const t_toktype type,
								t_line *line,
								t_tokenlst *lst);
t_code			token_str(const t_toktype type,
								t_line *line,
								t_tokenlst *lst);
t_code			token_str_wrapper(const t_toktype type,
									t_line *line,
									t_tokenlst *lst);
t_code			token_newline(t_line *line, t_tokenlst *lst);

/*
** Errors
*/

t_code			error_handler(t_errors error, t_toktype *token, t_line *line);

#endif
