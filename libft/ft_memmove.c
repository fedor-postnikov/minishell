/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:04:44 by dalfredi          #+#    #+#             */
/*   Updated: 2021/10/16 21:27:35 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_reverse(unsigned char *dest, unsigned char *src, size_t n)
{
	int		index;

	index = n - 1;
	while (index >= 0)
	{
		dest[index] = src[index];
		index--;
	}
}

static void	copy(unsigned char *dest, unsigned char *src, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		dest[index] = src[index];
		index++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s || n == 0)
		return (dest);
	if (s < d && d - s < (int)n)
	{
		copy_reverse(d, s, n);
		return (dest);
	}
	if (s > d && s - d < (int)n)
	{
		copy(d, s, n);
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
