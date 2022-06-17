/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:24:34 by dalfredi          #+#    #+#             */
/*   Updated: 2021/10/22 16:26:25 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p_list;

	if ((*lst) == NULL)
	{
		*lst = new;
		return ;
	}
	p_list = *lst;
	while (p_list->next)
		p_list = p_list->next;
	p_list->next = new;
}
