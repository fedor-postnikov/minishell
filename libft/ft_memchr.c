/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:15:41 by dalfredi          #+#    #+#             */
/*   Updated: 2021/10/19 18:40:51 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_ptr;

	mem_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)mem_ptr[i] == (unsigned char)c)
			return ((void *)(mem_ptr + i));
		i++;
	}
	return (NULL);
}
