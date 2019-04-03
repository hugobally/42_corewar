#include "asm.h"
#include "macros.h"
#include "types.h"
#include "errors.h"
#include "libft.h"

void					error_lexer(t_errors err, t_token *token, t_file *file)
{
	static t_errstr		tab[7] = {
		{label_badchar, "Forbidden char in label", 0, 0, 0},
		{label_badformat, "Bad formatting around symbol ':'", 0, 0, 0},
		{dir_badformat, "Bad formatting around symbol '%'", 0, 0, 0},
		{reg_badvalue, "Bad register [1 -", 1, REG_NUMBER, "]"},
		{cmd_unknown, "Unknown command", 0, 0, 0},
		{unknown_token, "Invalid token", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	if (token && file)
		build_errstr_tok(err, token, tab, file);
}

void					error_parser(t_errors err, t_token *token, t_file *file)
{
	static t_errstr		tab[12] = {
		{header_noquote, "Missing command parameter after", 0, 0, 0},
		{header_badquote, "Bad quote format", 0, 0, 0},
		{header_namesize, "Name is too long (Max ", 1, PROG_NAME_LENGTH, ")"},
		{header_commentsize, "Comment is too long (Max ", 1,
														COMMENT_LENGTH, ")"},
		{header_duplicate, "Duplicate command", 0, 0, 0},
		{expected_eol, "Expected end of instruction after ", 0, 0, 0},
		{label_duplicate, "Duplicate label", 0, 0, 0},
		{label_no_match, "No matching label found for ", 0, 0, 0},
		{bytesize, "Invalid champion size (Max ", 1, CHAMP_MAX_SIZE, "bytes )"},
		{expected_opcode, "Expected opcode here", 0, 0, 0},
		{param_invalid, "Invalid parameters for instruction ", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	if (token && file)
		build_errstr_tok(err, token, tab, file);
}

void					error_scanner(t_errors err, t_file *file)
{
	static t_errstr		tab[8] = {
		{malloc, "Malloc", 0, 0, 0},
		{open_error, "File could not be opened", 0, 0, 0},
		{read_crash, "Read Failure", 0, 0, 0},
		{read_linesize, "Line too big (Max", 1, GNL_MAX_LINE_LEN, "b)"},
		{filesize, "Input file too big (Max", 1, MAX_INPUT_FILE_SIZE, "b)"},
		{no_instructions, "No instructions found", 0, 0, 0},
		{header_missing, "Missing header command", 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	if (file)
		build_errstr_notok(err, tab, file);
}

t_code			error_handler(t_errors code, t_token *token, t_file *file)
{
	static int		error_count;
	static t_file	*current_file;

	if (file)
		current_file = file;
	else if (code == query)
		return (!error_count ? done : error);
	else
	{
		if (code < scanner_error)
			error_scanner(code, current_file);
		else if (code < lexer_error)
			error_lexer(code, token, current_file);
		else
			error_parser(code, token, current_file);
		error_count++;
		return (error);
	}
	return (done);
}
