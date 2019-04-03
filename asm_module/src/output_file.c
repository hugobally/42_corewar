#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "types.h"
#include "asm.h"

static t_code	output_instructions(t_tokenlst *lst, t_label **label_tab,
									t_file *file)
{
	t_token		*node;
	uint32_t	offset;

	offset = 0;
	node = lst->prog_start;
	while (node)
	{
		if (node->type == label && node->next->type != char_eol)
			node = node->next;
		else if (node->type == label)
			node = node->next->next;
		else
		{
			if (write_instruction(node, label_tab, file, &offset) == error)
				return (error);
			node = node->next;
			while (node && node->previous->type != char_eol)
				node = node->next;
		}
	}
	return (done);
}

static t_code	build_filename(t_file *file)
{
	size_t		name_len;

	name_len = ft_strlen(file->name);
	file->out_name = ft_strnew(name_len + 2);
	if (!file->out_name)
		return (error);
	ft_strncpy(file->out_name, file->name, name_len - 1);
	ft_strcpy(&(file->out_name[name_len - 1]), "cor");
	return (done);
}

t_code			output_file(t_tokenlst *lst,
							t_label **label_tab,
							header_t *header,
							t_file *file)
{
	(void)lst;
	(void)label_tab;
	(void)header;
	if (build_filename(file) == done)
	{
		if ((file->out_fd = open(file->out_name, O_CREAT | O_WRONLY
									| O_TRUNC | O_APPEND, 0644)) != -1)
		{
			if (write(file->out_fd, (void*)header, sizeof(header_t)) != -1)
				return (output_instructions(lst, label_tab, file));
		}
	}
	return (error);
}

//TODO
	//free file output name
	//handle bad names
	//check when name is only '.s'
	//check when open dir

//lst->now at zero on exit in scanner
