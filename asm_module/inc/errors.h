/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:47:47 by hbally            #+#    #+#             */
/*   Updated: 2019/04/26 17:26:55 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	read_linesize = -2,
	read_crash = -1,
	malloc,
	open_error,
	bad_filename,
	write_crash,
	filesize,
	no_instructions,
	header_missing,
	output_max_size,
	scanner_error,
	label_badchar,
	label_badformat,
	out_of_range,
	dir_badformat,
	reg_badvalue,
	cmd_unknown,
	unknown_token,
	lexer_error,
	header_noquote,
	badquote,
	header_namesize,
	header_commentsize,
	header_duplicate,
	expected_eol,
	expected_opcode,
	label_duplicate,
	label_no_match,
	param_invalid,
	parser_error,
	warning,
	bytesize,
	query,
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
