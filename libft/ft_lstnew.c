/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:27:51 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/21 07:23:37 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main(void)
// {
// 	t_list *new_node = ft_lstnew("Hello, World!");

// 	if (new_node)
// 	{
// 		printf("Contenu du nouveau noeud : %s\n", (char *)new_node->content);
// 		free(new_node);
// 	}
// 	else
// 		printf("Échec de création du nouveau noeud\n");
// 	return (0);
// }

// Cette fonction crée un nouveau nœud de liste chaînée avec le contenu donné.
// Voici ce que fait la fonction :
// Elle définit ft_lstnew qui prend un ptr void content en paramètre.
// À l'intérieur de la fonction, malloc pour une nouvelle structure t_list.
// Si malloc échoue, elle renvoie NULL pour indiquer une erreur.
// assigne le paramètre content au membre content
//  du nouveau nœud t_list nouvellement alloué.
// Elle initialise les pointeurs next du nouveau nœud à NULL,
//  en supposant qu'il s'agit d'une implémentation de liste chaînée double.
// Enfin, elle retourne un pointeur vers le nouveau nœud créé.
// Cette fonction crée un nouveau nœud pour une liste chaînée double,
// l'initialise avec le contenu donné,
//  puis retourne un pointeur vers ce nouveau nœud.