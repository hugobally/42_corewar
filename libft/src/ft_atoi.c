/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:00:42 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:03:46 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint64_t		get_number(const char *str, size_t i)
{
	uint64_t		n;
	size_t			len;

	n = 0;
	len = 0;
	while (ft_isdigit(str[i]))
	{
		len++;
		if (len > 10)
			return (0);
		if (!(n == 0 && str[i] == '0'))
			n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

int					ft_atoi(const char *str)
{
	size_t		i;
	int32_t		sign;
	uint64_t	u;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	sign = str[i] == '-' ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	u = get_number(str, i);
	if ((sign == 1 && u > 0x7FFFFFFFllu)
			|| (sign == -1 && u > 0x7FFFFFFFllu + 1llu))
		return (0);
	else
		return ((int32_t)u * sign);
}
