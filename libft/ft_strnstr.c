/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:54:54 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/10 12:25:00 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	if (big == NULL)
		*((char *)big - 1) = 0;
	while (len >= len_little)
	{
		len--;
		if (ft_memcmp(big, little, len_little) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
