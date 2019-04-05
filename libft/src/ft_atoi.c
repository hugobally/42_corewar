/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:00:42 by hbally            #+#    #+#             */
/*   Updated: 2019/04/05 18:12:44 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_number(const char *str, size_t i, int sign)
{
	int			n;

	n = 0;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int				ft_atoi(const char *str)
{
	size_t		i;
	size_t		len;
	int			sign;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	sign = str[i] == '-' ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	len = 0;
	while (ft_isdigit(str[i + len]))
		len++;
	if (len < 1 || len > 10)
		return (0);
	return (get_number(str, i, sign));
}
