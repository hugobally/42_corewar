#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

/*
** Add Single Char Token
*/

t_code				token_single(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
	t_token		template;

	template_init(&template, type, line);
	if (type != char_eol)
	{
		get_right_pad(&template, line);
		line->index++;
	}
	return (token_add(lst, &template, 1));
}

/*
**	Add Quote Token
*/

t_code				token_quote(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
	t_token		template;
	uint16_t	start;

	template_init(&template, type, line);
	start = ++(line->index);
	while (line->str[line->index] && line->str[line->index] != QUOTE_CHAR)
		line->index++;
	template.value = ft_strsub(line->str, start, line->index - start);
	if (line->str[line->index] == QUOTE_CHAR)
	{
		line->index++;
		template.pad = 1;
	}
	else
		template.pad = 0;
	return (token_add(lst, &template, ft_strlen(template.value)));
}

/*
**	Add Unknown Token /
*/

static uint8_t		endofstr(char c)
{
	return (c == COMMENT_CHAR
				|| c == LABEL_CHAR
				|| c == DIRECT_CHAR
				|| c == SEPARATOR_CHAR
				|| c == QUOTE_CHAR
				|| ft_iswhitespace(c));
}

static t_code		token_unknown(const t_toktype type,
											t_line *line,
											t_tokenlst *lst)
{
	t_token			template;
	uint16_t		start;

	template_init(&template, type, line);
	start = line->index;
	while (line->str[line->index + 1] && !endofstr(line->str[line->index + 1]))
		line->index++;
	get_right_pad(&template, line);
	template.value = ft_strsub(line->str, start, ++(line->index) - start);
	if (!(template.value))
		return (error_handler(malloc, 0, 0));
	else
		return (token_add(lst, &template, ft_strlen(template.value)));
}

t_code				token_unknown_wrapper(const t_toktype type,
												t_line *line,
												t_tokenlst *lst)
{
	if (ft_iswhitespace(line->str[line->index]))
	{
		line->index++;
		return (done);
	}
	else if (line->str[line->index] == '#')
	{
		while (line->str[line->index])
			line->index++;
		return (done);
	}
	else
		return (token_unknown(type, line, lst));
}
