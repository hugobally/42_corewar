/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:25:03 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 18:14:51 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t			ft_isnumstring(char *string, int32_t number)
{
	int32_t		i;
	int8_t		negative;

	negative = number < 0;
	i = (int32_t)(ft_strlen(string) - 1);
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
		return (!(i != 0 || string[0] != '-'));
	else
		return (!(i >= 0 && !(i == 0 && string[0] == '+')));
}
