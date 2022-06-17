/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:48:50 by bpono             #+#    #+#             */
/*   Updated: 2022/06/14 15:14:25 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strs_size(char **strs)
{
	int	len;

	if (strs == NULL)
		return (0);
	len = 0;
	while (strs[len])
		len++;
	return (len);
}

/*	Adds string at the end of strings array.
	String passed should be freeable.
*/
void	strs_append(char ***strs, char *value)
{
	char	**new_strs;
	int		i;
	int		len;

	i = 0;
	len = strs_size(*strs);
	new_strs = (char **)malloc(sizeof(char *) * (len + 2));
	if (new_strs == NULL)
		return ;
	if (*strs != NULL)
	{
		while ((*strs)[i])
		{
			new_strs[i] = (*strs)[i];
			i++;
		}
	}
	new_strs[i] = value;
	new_strs[i + 1] = NULL;
	free(*strs);
	*strs = new_strs;
}

char	**strs_copy(char **strs)
{
	int		i;
	int		len;
	char	**new_strs;

	i = 0;
	len = 0;
	len = strs_size(strs);
	new_strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (new_strs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_strs[i] = ft_strdup(strs[i]);
		if (new_strs[i] == NULL)
			return (NULL);
		i++;
	}
	new_strs[i] = NULL;
	return (new_strs);
}

void	strs_free(char ***strs)
{
	int	i;

	if (strs == NULL)
		return ;
	if (*strs != NULL)
	{
		i = 0;
		while ((*strs)[i] != NULL)
		{
			free((*strs)[i]);
			(*strs)[i] = NULL;
			i++;
		}
		free(*strs);
	}
	*strs = NULL;
}

/*	Returns 1 if value in list 'strs'
	Otherwise returns 0
*/
int	strs_in_list(char *value, char **strs)
{
	int	i;
	int	len;

	i = 0;
	len = strs_size(strs);
	while (i < len)
	{
		if (ft_strcmp(strs[i], value) == 0)
			return (1);
		i++;
	}
	return (0);
}
