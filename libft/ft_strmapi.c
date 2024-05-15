/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:26:25 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/16 10:56:29 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// static char	test_function(unsigned int index, char c)
// {
// 	return (c + 1);
// }

// int	main(void)
// {
// 	const char	*str = "abcdef";
// 	char		*result = ft_strmapi(str, test_function);

// 	if (result != NULL)
// 	{
// 		printf("Résultat de ft_strmapi : %s\n", result);
// 		free(result);
// 	}
// 	else
// 		printf("Erreur : la fonction ft_strmapi a retourné NULL.\n");
// 	return (0);
// }
