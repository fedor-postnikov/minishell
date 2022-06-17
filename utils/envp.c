/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:13:43 by bpono             #+#    #+#             */
/*   Updated: 2022/06/14 16:36:00 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Joins three strings and returns malloced string.
*/
char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

/*	Sets envp variable value
*/
int	env_set(char *name, char *value)
{
	int	len;
	int	i;

	len = strs_size(g_data.envp);
	if (len == 0)
	{
		strs_append(&g_data.envp, ft_strjoin3(name, "=", value));
		return (0);
	}
	name = ft_strjoin(name, "=");
	i = 0;
	while (g_data.envp[i] != NULL)
	{
		if (ft_strncmp(name, g_data.envp[i], ft_strlen(name)) == 0)
		{
			free(g_data.envp[i]);
			g_data.envp[i] = ft_strjoin(name, value);
			free(name);
			return (0);
		}
		i++;
	}
	strs_append(&g_data.envp, ft_strjoin(name, value));
	free(name);
	return (0);
}

/*	Returns a pointer to envp variable value.
	Do not free or change returned value.
*/
char	*env_get(char *name)
{
	int		i;
	int		len;
	int		size;

	i = 0;
	name = ft_strjoin(name, "=");
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	size = strs_size(g_data.envp);
	if (g_data.envp == NULL)
		return (NULL);
	while (g_data.envp[i] != NULL && ft_strncmp(g_data.envp[i], name, len))
		i++;
	if (i == size)
	{
		free(name);
		return (NULL);
	}
	free(name);
	return (g_data.envp[i] + len);
}

/*	Return 0 if deleted successfully, 1 otherwise
*/
int	env_delete(char *name)
{
	char	*value;
	char	*var_string;

	value = env_get(name);
	if (value == NULL)
		return (1);
	var_string = ft_strjoin3(name, "=", value);
	strs_delete(&g_data.envp, var_string);
	free(var_string);
	return (0);
}
