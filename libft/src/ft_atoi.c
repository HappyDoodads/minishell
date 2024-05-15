/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:12:32 by jdemers           #+#    #+#             */
/*   Updated: 2023/10/19 10:11:00 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f')
		return (1);
	if (c == '\r' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	short	sign;
	int		pow10;
	int		total;

	i = 0;
	sign = 1;
	pow10 = 1;
	total = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (--i >= 0)
	{
		total += (str[i] - 48) * pow10 * sign;
		pow10 *= 10;
	}
	return (total);
}
