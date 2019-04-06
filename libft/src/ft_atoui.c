#include "libft.h"

static uint32_t		get_number(const char *str, size_t i)
{
	uint32_t		n;

	n = 0;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

uint32_t			ft_atoui(const char *str)
{
	size_t			i;
	size_t			len;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	len = 0;
	while (ft_isdigit(str[i + len]))
		len++;
	return (get_number(str, i));
}
