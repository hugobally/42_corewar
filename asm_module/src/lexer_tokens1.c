#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

void			template_init(t_token *template, t_toktype type, t_line *line)
{
	ft_bzero(template, sizeof(t_token));
	template->type = type;
	template->pos = line->num | (((uint32_t)(line->index) + 1u) << 16);
	if (line->index == 0 || ft_iswhitespace(line->str[line->index - 1]))
		template->pad |= PAD_LEFT;
}

void			get_right_pad(t_token *template, t_line *line)
{
	if (line->str[line->index + 1] == '\0'
			|| ft_iswhitespace(line->str[line->index + 1]))
		template->pad |= PAD_RIGHT;
}

t_code			token_single(const t_toktype type,
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

t_code			token_quote(const t_toktype type,
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
