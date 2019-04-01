#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

t_token				*find_before(t_token *start, t_toktype type)
{
	t_token			*node;

	node = start;
	while (node)
	{
		if (node->type == type)
			return (node);
		node = node->previous;
	}
	return (start);
}

t_code				get_header_value(t_token *node, header_t *header)
{
	if (node->type == cmd_name)
	{
		node = node->next;
		if (ft_strlen(node->value) > PROG_NAME_LENGTH)
			return (error_handler(header_namesize, node, 0));
		if (header->prog_name[0])
			return (error_handler(header_duplicate, node, 0));
		ft_strcpy(header->prog_name, node->value);
	}
	if (node->type == cmd_comment)
	{
		node = node->next;
		if (ft_strlen(node->value) > COMMENT_LENGTH)
			return (error_handler(header_commentsize, node, 0));
		if (header->comment[0])
			return (error_handler(header_duplicate, node, 0));
		ft_strcpy(header->prog_name, node->value);
	}
	if (!node->next || node->next->type != char_eol)
		return (error_handler(expected_eol, node, 0));
	return (done);
}

t_code				is_valid_cmd(t_token *node)
{
	if (!node || node->type != cmd_name || node->type != cmd_comment)
		return (error_handler(header_missing, node, 0));
	if (!(node->next && node->type == quote))
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
	while (cmd_count < 2)
	{
		if (node && node->type == char_eol)
			node = node->next;
		else
		{
			if (is_valid_cmd(node) == error)
				return (error);
			else
			{
				node = node->next;
				if (get_header_value(node, header) == error)
					return (error);
				node = node->next->next;
				cmd_count++;
			}
		}
	}
	lst->prog_start = node;
	return (done);
}

t_code				parser(t_tokenlst *lst, t_file *file)
{
	t_label			*label_tab;
	header_t		header;

//	if (!lst->start)
//		return (error);
//	ft_bzero(&header, sizeof(header_t));
//	if (get_header(lst, &header) == error)
//		return (error);
	(void)label_tab;
	(void)file;
	(void)lst;
	(void)header;
//	build_label_tab(lst, label_tab);
//	header.prog_size += syntax_check(lst);
	//output

	return (done);
}
