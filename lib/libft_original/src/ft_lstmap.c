/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:37 by jrichir           #+#    #+#             */
/*   Updated: 2023/11/08 16:10:29 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mod_list;
	t_list	*mod_node;
	char	*s;

	if (!lst || !f || !del)
		return (NULL);
	mod_list = NULL;
	while (lst)
	{
		s = (*f)(lst->content);
		mod_node = ft_lstnew(s);
		if (!mod_node)
		{
			(*del)(s);
			ft_lstclear(&mod_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&mod_list, mod_node);
		lst = lst->next;
	}
	return (mod_list);
}
