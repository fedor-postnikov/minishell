/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:21:56 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/10 11:00:08 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(const char *str, char sep)
{
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i] != '\0')
			i++;
		while (str[i] != sep && str[i] != '\0')
			i++;
		counter++;
	}
	if (counter > 0 && str[i - 1] == sep)
		counter--;
	return (counter);
}

static char	**clear_words(char **words)
{
	char	**ptr;

	ptr = words;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(words);
	return (NULL);
}

static char	**split_n(const char *s, char c,
					unsigned int words_count, char **words)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	while (i < words_count)
	{
		while (*s == c && *s != '\0')
			s++;
		len = 0;
		while (s[len] != c && s[len] != '\0')
			len++;
		words[i] = ft_substr(s, 0, len);
		if (words[i] == NULL)
			return (clear_words(words));
		s = s + len;
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char			**words;
	unsigned int	words_count;

	if (s == NULL)
		return (NULL);
	words_count = count_words(s, c);
	words = (char **)malloc((words_count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	return (split_n(s, c, words_count, words));
}
