/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:57:36 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

uint32_t		reverse_endian(uint32_t number)
{
	uint32_t	test_endian;
	uint32_t	output;

	test_endian = 1;
	if ((uint32_t)(((uint8_t*)&test_endian)[0]))
	{
		output = 0;
		output |= (number & 0x000000FF) << 24;
		output |= (number & 0x0000FF00) << 8;
		output |= (number & 0x00FF0000) >> 8;
		output |= (number & 0xFF000000) >> 24;
		return (output);
	}
	else
		return (number);
}

static t_code	output_instructions(t_tokenlst *lst, t_label **label_tab,
									t_file *file)
{
	t_token		*node;
	uint32_t	offset;

	offset = 0;
	node = lst->prog_start;
	while (node)
	{
		if (node->type == label && node->next->type == opcode)
			node = node->next;
		else if (node->type == label)
			node = skip_eol(node);
		else
		{
			if (write_instruction(node, label_tab, file, &offset) == error)
				return (error);
			node = skip_eol(node);
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
							t_header *header,
							t_file *file)
{
	header->magic = reverse_endian(header->magic);
	header->prog_size = reverse_endian(header->prog_size);
	if (build_filename(file) == done)
	{
		if ((file->out_fd = open(file->out_name, O_CREAT | O_WRONLY
									| O_TRUNC | O_APPEND, 0644)) != -1)
		{
			ft_dprintf(1, "%s%s: %sWriting output to %s%s%s\n",
						WHT, file->name, BLU, WHT, file->out_name, RESET);
			if (write(file->out_fd, (void*)header, sizeof(t_header)) != -1)
				return (output_instructions(lst, label_tab, file));
		}
	}
	return (error);
}
