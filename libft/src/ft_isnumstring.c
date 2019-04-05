/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:25:03 by hbally            #+#    #+#             */
/*   Updated: 2019/04/05 19:09:08 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint8_t	check_sizes(char *string, size_t string_len,
								int32_t number, int8_t negative)
{
	size_t		number_len;

	number_len = 1;
	while (ft_abs32(number) >= 10)
	{
		number /= 10;
		number_len++;
	}
	return (number_len + (negative || string[0] == '+') == string_len);
}

uint8_t			ft_isnumstring(char *string, int32_t number)
{
	int32_t		i;
	int8_t		negative;
	size_t		len;

	if (number == -2147483648)
		return (ft_strcmp(string, "-2147483648") == 0);
	negative = number < 0;
	len = ft_strlen(string);
	if (!string || !check_sizes(string, len, number, negative))
		return (0);
	i = len - 1;
	while (i >= 0)
	{
		if (ft_abs32(number % 10) != string[i] - '0')
			return (0);
		i--;
		if (ft_abs32(number) < 10)
			break ;
		else
			number /= 10;
	}
	if (negative)
		return (i == 0 && string[0] == '-');
	else
		return (i < 0 || (i == 0 && string[0] == '+'));
}
