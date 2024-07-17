/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:54:08 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/17 16:40:28 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isset(int c, const char *set)
{
	if (c == 0)
		return (0);
	while (*set)
	{
		if (c == (int)*set)
			return (1);
		set++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
