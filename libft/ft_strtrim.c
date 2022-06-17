/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:43:16 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/10 12:38:24 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set != c && *set != '\0')
		set++;
	if (*set == '\0' && c != '\0')
		return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != '\0' && is_in_set(*s1, set))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && is_in_set(s1[i], set))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
