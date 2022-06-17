/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:55:58 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/17 16:36:42 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_command(char *cmd, char **paths)
{
	char	*path;
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths[i] != NULL && ft_strcmp(cmd, "") != 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			strs_free(&paths);
			return (path);
		}
		else
			free(path);
		i++;
	}
	strs_free(&paths);
	return (NULL);
}

static char	*parse_path(char *cmd)
{
	char	**paths;
	char	*path_env_value;

	path_env_value = env_get("PATH");
	if (path_env_value == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
		return (NULL);
	}
	paths = ft_split(path_env_value, ':');
	if (!paths)
		exit(func_error("ft_split"));
	return (find_command(cmd, paths));
}

char	*get_full_path(char	*cmd)
{
	char	*full_path;

	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_strdup(cmd));
	full_path = parse_path(cmd);
	if (full_path == NULL)
		return (ft_strdup(cmd));
	return (full_path);
}
