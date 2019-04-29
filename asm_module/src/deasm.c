/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:45:14 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "asm.h"
#include "errors.h"
#include "libft.h"
#include "types.h"
#include "libcorewar.h"

static t_code		deasm_error(t_file *file)
{
	ft_dprintf(2, "%sDeassembly error : '%s'%s\n", RED, file->name, RESET);
	return (error);
}

static int16_t		build_filename(t_file *file)
{
	size_t			name_len;

	name_len = ft_strlen(file->name);
	file->fd = open(file->name, O_RDONLY);
	if (file->fd == -1 || name_len < 4
			|| ft_strcmp(&(file->name[name_len - 4]), ".cor"))
		return (1);
	file->out_name = ft_strnew(name_len - 2);
	if (!file->out_name)
		return (1);
	ft_strncpy(file->out_name, file->name, name_len - 2);
	file->out_name[name_len - 3] = 's';
	return (done);
}

static int			print_param(t_file *file, t_op *op,
									uint8_t code, uint8_t index)
{
	uint8_t			type;
	int32_t			buff;
	uint8_t			*ptr;

	buff = 0;
	ptr = (uint8_t*)&buff;
	type = (code & (0xC0 >> index * 2)) >> (6 - index * 2);
	if (type == REG_CODE)
	{
		read(file->fd, ptr, 1);
		return (ft_dprintf(file->out_fd, "r%d", buff));
	}
	if (type == DIR_CODE)
		ft_dprintf(file->out_fd, "%%");
	if (type == IND_CODE || op->compact)
	{
		read(file->fd, ptr + 1, 1);
		read(file->fd, ptr, 1);
		return (ft_dprintf(file->out_fd, "%d", *((int16_t*)ptr)));
	}
	else
	{
		read(file->fd, &buff, 4);
		return (ft_dprintf(file->out_fd, "%d", (int32_t)reverse_endian(buff)));
	}
}

static t_code		print_op(t_file *file, t_op *op)
{
	uint8_t			index;
	uint8_t			bytecode;

	ft_dprintf(file->out_fd, "%s\t", op->name);
	index = 0;
	if (op->has_ocp)
		read(file->fd, &bytecode, 1);
	while (index < op->param_num)
	{
		if (!(op->has_ocp))
		{
			if (op->param_types[index] & T_REG)
				bytecode = 0x55;
			else if (op->param_types[index] & T_DIR)
				bytecode = 0xAA;
			else
				bytecode = 0xFF;
		}
		print_param(file, op, bytecode, index);
		index++;
		if (index != op->param_num)
			ft_dprintf(file->out_fd, ", ");
	}
	ft_dprintf(file->out_fd, "\n");
	return (done);
}

t_code				deasm(t_file *file)
{
	t_header		header;
	int16_t			status;
	uint8_t			buff;

	status = 0;
	status += build_filename(file);
	status += read(file->fd, &header, sizeof(t_header))
				< (long)sizeof(t_header);
	status += (file->out_fd = open(file->out_name,
				O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)) == -1;
	if (status)
		return (deasm_error(file));
	ft_dprintf(file->out_fd, ".name \"%s\"\n", header.prog_name);
	ft_dprintf(file->out_fd, ".comment \"%s\"\n\n", header.comment);
	while (read(file->fd, &buff, 1) > 0)
	{
		if (buff < 1 || buff > 16)
			return (deasm_error(file));
		if (print_op(file, &(g_op_tab[buff - 1])) == error)
			return (deasm_error(file));
	}
	ft_printf("%sDisassembly complete >> %s\n",
				BLU, file->out_name, RESET);
	return (done);
}
