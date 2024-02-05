/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:22:41 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:45 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*first_node;

	if (!lst || !f || !del)
		return (NULL);
	first_node = NULL;
	while (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		if (!(new_list))
		{
			while (first_node != NULL)
			{
				new_list = first_node->next;
				del(first_node->content);
				free(first_node);
				first_node = new_list;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first_node, new_list);
		lst = lst->next;
	}
	return (first_node);
}
