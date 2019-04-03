#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

static t_code		get_header_value(t_token *node, header_t *header)
{
	if (node->previous->type == cmd_name)
	{
		if (ft_strlen(node->value) > PROG_NAME_LENGTH)
			return (error_handler(header_namesize, node, 0));
		if (header->prog_name[0])
			return (error_handler(header_duplicate, node->previous, 0));
		ft_strcpy(header->prog_name, node->value);
	}
	if (node->previous->type == cmd_comment)
	{
		if (ft_strlen(node->value) > COMMENT_LENGTH)
			return (error_handler(header_commentsize, node, 0));
		if (header->comment[0])
			return (error_handler(header_duplicate, node->previous, 0));
		ft_strcpy(header->comment, node->value);
	}
	if (!node->next || node->next->type != char_eol)
		return (error_handler(expected_eol, node, 0));
	return (done);
}

static t_code		is_valid_cmd(t_token *node)
{
	if (!node || !(node->type == cmd_name || node->type == cmd_comment))
		return (error_handler(header_missing, 0, 0));
	if (!(node->next && node->next->type == quote))
		return (error_handler(header_noquote, node, 0));
	node = node->next;
	if (!ft_strlen(node->value) || !node->pad)
		return (error_handler(header_badquote, node, 0));
	return (done);
}

t_code				get_header(t_tokenlst *lst, header_t *header)
{
	t_token			*node;
	int				cmd_count;

	node = lst->start;
	cmd_count = 0;
	while (node && cmd_count < 2)
	{
		if (is_valid_cmd(node) != error)
		{
			node = node->next;
			if (get_header_value(node, header) == error)
				return (error);
			node = node->next->next;
			cmd_count++;
		}
		else
			return (error);
	}
	if (cmd_count != 2)
		return (error_handler(header_missing, 0, 0));
	lst->prog_start = node;
	return (done);
}
