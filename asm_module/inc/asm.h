#ifndef ASM_H
# define ASM_H

# include "types.h"
# include "string.h"

/*
**	DEBUG
*/

void			debug_printtokenlst(t_tokenlst *lst);//

/*
** Lexer Scanner
*/

t_code			lexer_scanner(const int fd);
t_code			lexer_exit(t_tokenlst *lst, t_errors code);
void			template_init(t_token *template, t_toktype type, t_line *line);
void			get_right_pad(t_token *template, t_line *line);
t_code			token_add(t_tokenlst *lst, const t_token *template,
									const size_t value_size);
t_code			token_single(const t_toktype type,
								t_line *line, t_tokenlst *lst);
t_code			token_unknown(const t_toktype type,
									t_line *line, t_tokenlst *lst);
t_code			token_newline(t_line *line, t_tokenlst *lst);
t_code			token_quote(const t_toktype type,
								t_line *line,
								t_tokenlst *lst);

/*
** Lexer Checker
*/

t_code			lexer_checker(t_tokenlst *lst);
void			find_labels_pass1(t_token *token);
void			find_labels_pass2(t_token *token);
void			find_opcodes(t_token *token);
t_op			*find_op(char *string);

/*
** Errors
*/

t_code			error_handler(t_errors error, t_token *token, t_line *line);

#endif
