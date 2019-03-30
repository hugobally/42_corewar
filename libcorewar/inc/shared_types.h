/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:52:53 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 17:19:02 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TYPE_H
# define OP_TYPE_H

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
	uint8_t			boolvalue1_no_idea_wtf_it_does;
	uint8_t			boolvalue2_no_idea_wtf_it_does;
}					t_op;

extern t_op 		g_op_tab[17];

#endif
