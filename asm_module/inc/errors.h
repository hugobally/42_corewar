#ifndef ERRORS_H
# define ERRORS_H

# define RED   "\033[1;31m"
# define GRN   "\033[1;32m"
# define YEL   "\033[33m"
# define BLU   "\033[34m"
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
	filesize, //no token, critical -- more than max_token tokens

	critical_error,

	label_badchar,//forbidden chars
	label_badformat,//example : 'label : (...)' '%: label'
	dir_badformat, //example : '  % 50  ' ' % ' ' % :label'
	reg_badvalue,//r100, rBLA, etc
	cmd_unknown,//.toto
	unknown_token,//djsafkashf
	quote_unterminated, //no token -- no critical
	quote_empty,

	lexer_error,
	
	syntax_error,
	//special codes
	query, // query error_handler to see if errors have occured
	err,
	no_err
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
