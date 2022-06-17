/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:35:24 by dalfredi          #+#    #+#             */
/*   Updated: 2021/10/20 12:27:25 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*dup;
	unsigned int	str_len;

	str_len = ft_strlen(s);
	dup = (char *)malloc((str_len + 1) * sizeof(char));
	if (dup)
	{
		ft_memcpy(dup, s, str_len + 1);
		return (dup);
	}
	return (NULL);
}
