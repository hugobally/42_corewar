#ifndef ERRORS_H
# define ERRORS_H

# include <stdint.h>

# define RED   "\033[1;31m"
# define GRN   "\033[1;32m"
# define YEL   "\033[33m"
# define BLU   "\033[1;34m"
# define MAG   "\033[35m"
# define CYN   "\033[36m"
# define WHT   "\033[1;37m"
# define RESET "\033[0m"

typedef enum		e_errors
{
	open_error = -3,
	read_linesize = -2,//no token, critical -- one line is > than max line size
	read_crash = -1,//no token, critical
	malloc = 0,//no token, critical
	write_crash,
	filesize, //no token, critical -- more than max_token tokens
	no_instructions,
	header_missing,//name/comment not at top

	scanner_error,

	label_badchar,//forbidden chars
	label_badformat,//example : 'label : (...)' '%: label'
	out_of_range, //> max int 
	dir_badformat, //example : '  % 50  ' ' % ' ' % :label'
	reg_badvalue,//r100, rBLA, etc
	cmd_unknown,//.toto
	unknown_token,//djsafkashf

	lexer_error,
	
	header_noquote,//missing quote after cmd
	header_badquote,//unterminated or empty quote
	header_namesize,
	header_commentsize,
	header_duplicate,//.name (...) .name
	
	expected_eol,
	expected_opcode,
	label_duplicate, //same label appears more than once
	label_no_match, //:label1 but label1 not found in file
	bytesize, //champion too big or huge file
	param_invalid,//wrong parameter for instruction

	parser_error,
	//special codes
	query, // query error_handler to see if errors have occured
	no_error
}					t_errors;

typedef struct		s_errstr
{
	t_errors		errcode;
	char			*str1;
	uint8_t			has_extra;
	int				num_value;
	char			*str2;
}					t_errstr;

#endif
