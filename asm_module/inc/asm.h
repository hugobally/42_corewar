#ifndef ASM_H
# define ASM_H

# include "types.h"
# include "errors.h"
# include "string.h"

/*
**	DEBUG
*/

void		debug_printtokenlst(t_tokenlst *lst);//
void		debug_print_label_tab(t_label **label_tab);//

/*
** Scanner
*/

t_code		scanner(t_file *file);
void		template_init(t_token *template, t_toktype type, t_line *line);
void		get_right_pad(t_token *template, t_line *line);
t_code		token_add(t_tokenlst *lst, const t_token *template,
						const size_t value_size);

t_code		token_single(const t_toktype type, t_line *line, t_tokenlst *lst);
t_code		token_unknown_wrapper(const t_toktype type, t_line *line,
									t_tokenlst *lst);

t_code		token_newline(t_line *line, t_tokenlst *lst);
t_code		token_quote(const t_toktype type, t_line *line, t_tokenlst *lst);

/*
** Lexer
*/

t_code		lexer(t_tokenlst *lst, t_file *file);
void		find_labels(t_token *token);
void		find_opcodes(t_token *token);
void		find_registers(t_token *token);
void		find_num(t_token *token);
void		find_commands(t_token *token);
t_op		*find_op(char *string);

/*
** Parser
*/

t_code		syntax(t_tokenlst *lst, t_file *file);
t_code		get_header(t_tokenlst *lst, header_t *header);
t_code		build_label_tab(t_tokenlst *lst, t_label **label_tab);
t_label		*label_tab_fetch(t_token *token, t_label **label_tab);
t_code		syntax_prog(t_tokenlst *lst, t_label **label_tab, header_t *header);

/*
** Output
*/

t_code			output_file(t_tokenlst *lst,
								t_label **label_tab,
								header_t *header,
								t_file *file);
t_code			write_instruction(t_token *token, t_label **label_tab,
									t_file *file, uint32_t *offset);

/*
** Errors
*/

t_code		error_handler(t_errors error, t_token *token, t_file *file);
void		error_scanner(t_errors err, t_file *file);
void		error_parser(t_errors err, t_token *token, t_file *file);
void		error_lexer(t_errors err, t_token *token, t_file *file);
void		build_errstr_notok(t_errors error, t_errstr *tab, t_file *file);
void		build_errstr_tok(t_errors error, t_token *token, t_errstr *tab,
								t_file *file);

/*
** Free
*/

void		token_del(t_token *token, t_tokenlst *lst);
t_code		syntax_exit(t_label **label_tab, header_t *header, t_errors error);
t_code		scanner_exit(t_tokenlst *lst, t_errors code);

#endif
