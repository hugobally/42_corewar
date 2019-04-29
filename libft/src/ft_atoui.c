/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:04:13 by rle-ru            #+#    #+#             */
/*   Updated: 2019/04/29 14:04:13 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint32_t		get_number_hex(const char *str, size_t i)
{
	uint32_t		n;

	n = 0;
	while (str[i] && ft_strchr("0123456789AaBbCcDdEeFf", str[i]))
	{
		if (!(n == 0 && str[i] == '0'))
		{
			if (str[i] >= 'A' && str[i] <= 'F')
				n = n * 16 + (uint32_t)ft_strchri("0123456789ABCDEF", str[i]);
			else
				n = n * 16 + (uint32_t)ft_strchri("0123456789abcdef", str[i]);
		}
		i++;
	}
	return (n);
}

static uint32_t		get_number(const char *str, size_t i)
{
	uint32_t		n;

	n = 0;
	while (ft_isdigit(str[i]))
	{
		if (!(n == 0 && str[i] == '0'))
			n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

uint32_t			ft_atoui(const char *str)
{
	size_t			i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '0' && str[i + 1] && ft_strchr("xX", str[i + 1]))
		return (get_number_hex(str, i + 2));
	i += str[i] == '+' ? 1 : 0;
	return (get_number(str, i));
}
