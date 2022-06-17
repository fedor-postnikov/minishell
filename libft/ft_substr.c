/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:25:59 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/10 11:02:09 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	str_len;
	unsigned int	substr_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (str_len - start < len)
		substr_len = str_len - start;
	else
		substr_len = len;
	sub_str = (char *)malloc((substr_len + 1) * (sizeof(char)));
	if (sub_str == NULL)
		return (NULL);
	ft_memcpy(sub_str, s + start, substr_len);
	sub_str[substr_len] = '\0';
	return (sub_str);
}
