/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:08:15 by jerem             #+#    #+#             */
/*   Updated: 2024/02/09 12:08:15 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("\nreturn 1 is digit else return \n"
// 	"\nresult : %d\n\n", ft_isalpha('a'));
// 	return (0);
// }
