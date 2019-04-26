/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:52:02 by hbally            #+#    #+#             */
/*   Updated: 2019/04/26 17:27:37 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "macros.h"
#include "types.h"
#include "errors.h"
#include "libft.h"

void					error_warning(t_errors err, t_token *token,
										t_file *file)
{
	static t_errstr		tab[2] = {
		{bytesize, "/Invalid champ size (Max", 1, CHAMP_MAX_SIZE, " bytes) at"},
		{0, 0, 0, 0, 0}
	};

	if (file)
	{
		if (token)
			build_errstr_tok(err, token, tab, file);
		else
			build_errstr_notok(err, tab, file);
	}
}

void					error_lexer(t_errors err, t_token *token, t_file *file)
{
	static t_errstr		tab[8] = {
		{label_badchar, "Forbidden char in label", 0, 0, 0},
		{label_badformat, "Bad formatting around symbol ':'", 0, 0, 0},
		{dir_badformat, "Bad formatting around symbol '%'", 0, 0, 0},
		{reg_badvalue, "Bad register [1 -", 1, REG_NUMBER, "]"},
		{cmd_unknown, "Unknown command", 0, 0, 0},
		{unknown_token, "Invalid token", 0, 0, 0},
		{out_of_range, "Value out of range", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	if (token && file)
		build_errstr_tok(err, token, tab, file);
}

void					error_parser(t_errors err, t_token *token, t_file *file)
{
	static t_errstr		tab[11] = {
		{header_noquote, "Missing command parameter after", 0, 0, 0},
		{badquote, "Bad command format around ", 0, 0, 0},
		{header_namesize, "Name is too long (Max", 1, PROG_NAME_LENGTH, ")"},
		{header_commentsize, "Comment too long (Max", 1, COMMENT_LENGTH, ")"},
		{header_duplicate, "Duplicate command", 0, 0, 0},
		{expected_eol, "Expected end of instruction after", 0, 0, 0},
		{label_duplicate, "Duplicate label", 0, 0, 0},
		{label_no_match, "No matching label found for", 0, 0, 0},
		{expected_opcode, "Expected opcode here", 0, 0, 0},
		{param_invalid, "Invalid parameters for instruction", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	if (token && file)
		build_errstr_tok(err, token, tab, file);
}

void					error_scanner(t_errors err, t_file *file)
{
	static t_errstr		tab[11] = {
		{malloc, "Malloc", 0, 0, 0},
		{bad_filename, "Bad file suffix", 0, 0, 0},
		{open_error, "File could not be opened or does not exist", 0, 0, 0},
		{read_crash, "Read Failure", 0, 0, 0},
		{read_linesize, "Line too big (Max", 1, GNL_MAX_LINE_LEN, "b)"},
		{filesize, "File too big (>", 1, MAX_INPUT_FILE_SIZE / 1000000, "MB)"},
		{no_instructions, "No instructions found", 0, 0, 0},
		{header_missing, "Missing header command", 0, 0, 0},
		{write_crash, "Write Failure", 0, 0, 0},
		{output_max_size, "Outputsize > IND_MAX", 1, MAX_OUTPUT_BYTE_SIZE, ""},
		{0, 0, 0, 0, 0}
	};

	if (file)
		build_errstr_notok(err, tab, file);
}

t_code					error_handler(t_errors code,
										t_token *token, t_file *file)
{
	static int			error_count;
	static t_file		*current_file;

	if (file)
	{
		current_file = file;
		error_count = 0;
	}
	else if (code == query)
		return (!error_count ? done : error);
	else
	{
		if (code < scanner_error)
			error_scanner(code, current_file);
		else if (code < lexer_error)
			error_lexer(code, token, current_file);
		else if (code < parser_error)
			error_parser(code, token, current_file);
		else
			error_warning(code, token, current_file);
		if (code < warning)
			error_count++;
		return (error);
	}
	return (done);
}
