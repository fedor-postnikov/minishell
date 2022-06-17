/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:33:45 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/03 09:31:42 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;	
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst > size)
		len_dst = size;
	if (len_dst == size)
		return (len_dst + len_src);
	if (len_src + len_dst < size)
	{
		ft_memcpy(dst + len_dst, src, len_src + 1);
	}
	else
	{
		ft_memcpy(dst + len_dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len_dst + len_src);
}
