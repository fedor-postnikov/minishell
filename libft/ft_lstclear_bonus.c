/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:29:37 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/03 09:35:40 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		del(prev->content);
		free(prev);
	}
	*lst = NULL;
}
