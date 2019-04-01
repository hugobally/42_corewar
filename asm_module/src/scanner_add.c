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

t_code					token_add(t_tokenlst *lst, const t_token *template,
									const size_t value_size)
{
	t_token				*new;
	static size_t		stored_size;

	if (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
		return (error_handler(malloc, 0, 0));
	new->value = template->value;
	new->type = template->type;
	new->pos = template->pos;
	new->pad = template->pad;
	new->previous = lst->end;
	if (!lst->start)
		lst->start = new;
	if (lst->end)
		lst->end->next = new;
	lst->end = new;
	stored_size += value_size;
	if (stored_size > MAX_INPUT_FILE_SIZE)
		return (error_handler(filesize, 0, 0));
	return (done);
}
