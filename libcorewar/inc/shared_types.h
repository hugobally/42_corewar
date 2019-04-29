/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:52:53 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 13:57:01 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_TYPES_H
# define SHARED_TYPES_H

# include <stdint.h>

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef struct		s_op
{
	char			*name;
	uint8_t			param_num;
	uint8_t			param_types[3];
	uint8_t			opcode;
	uint32_t		cycles;
	char			*info;
	uint8_t			has_ocp;
	uint8_t			compact;
}					t_op;

extern t_op			g_op_tab[17];

#endif
