/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:06:27 by bpono             #+#    #+#             */
/*   Updated: 2022/06/17 17:01:09 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_error(char *value, char *cd)
{
	ft_putstr_fd(value, 2);
	ft_putstr_fd(cd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(1, "\n", 2);
	return (1);
}

static int	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

char	*get_path(char *value)
{
	if (value == NULL || (ft_strcmp(value, "~") == 0))
		return (env_get("HOME"));
	else
		return (value);
}

int	cd_proces_minus(void)
{
	char	cwd[PATH_MAX];
	int		c;
	char	*cd;

	getcwd(cwd, PATH_MAX);
	cd = ft_strdup(env_get("OLDPWD"));
	if (cd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	env_set("OLDPWD", cwd);
	c = chdir(cd);
	if (c == -1)
	{
		free(cd);
		return (str_error("minishell: cd: ", cd));
	}
	free(cd);
	getcwd(cwd, PATH_MAX);
	env_set("PWD", cwd);
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	return (0);
}

/*	Change directory
*/
int	cd(char **args)
{
	char	*cd;
	char	cwd[PATH_MAX];
	int		c;
	char	*value;

	if (strs_size(args) > 2)
		return (print_error("minishell: cd: too many arguments"));
	value = args[1];
	if (value != NULL && ft_strcmp(value, "-") == 0)
		return (cd_proces_minus());
	cd = get_path(value);
	if (cd == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	getcwd(cwd, PATH_MAX);
	env_set("OLDPWD", cwd);
	c = chdir(cd);
	if (c == -1)
		return (str_error("minishell: cd: ", cd));
	getcwd(cwd, PATH_MAX);
	env_set("PWD", cwd);
	return (0);
}
