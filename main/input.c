/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:16:21 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/14 21:53:46 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Returns 1 if string contains only spaces and tabs, 0 otherwise
*/
int	string_is_blank(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/*	Read a string, and return a pointer to it.
	Returns NULL on EOF.
*/
char	*get_line(void)
{
	static char	*line_read = (char *) NULL;
	char		*prompt;

	if (line_read != NULL)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	prompt = make_prompt(DEFAULT_PROMPT);
	line_read = readline (prompt);
	free(prompt);
	if (line_read && *line_read)
	{
		if (string_is_blank(line_read) == 0)
			add_history (line_read);
	}
	return (line_read);
}

/*	Mallocs new prompt
*/
char	*make_prompt(char *prompt)
{
	char	*path;
	char	*full_prompt;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (path == NULL)
		return (NULL);
	full_prompt = ft_strjoin(path, prompt);
	free(path);
	return (full_prompt);
}
