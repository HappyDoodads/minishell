/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:54:07 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/20 11:29:19 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// int main()
// {
// 	t_list *node1 = malloc(sizeof(t_list));
// 	t_list *node2 = malloc(sizeof(t_list));
// 	t_list *node3 = malloc(sizeof(t_list));

// 	node1->content = NULL;
// 	node2->content = NULL;
// 	node3->content = NULL;
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = NULL;
// 	int size = ft_lstsize(node1);

// 	printf("Taille de la liste chaînée : %d\n", size);
// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
