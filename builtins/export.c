/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:32:33 by bpono             #+#    #+#             */
/*   Updated: 2022/06/14 15:15:02 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	sort(char ***to_export)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	size = strs_size(*to_export);
	if (size == 0)
		return (1);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp((*to_export)[j], (*to_export)[j + 1]) > 0)
			{
			tmp = (*to_export)[j];
			(*to_export)[j] = (*to_export)[j + 1];
			(*to_export)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	write_list(char **list)
{
	int		l;
	char	*value;

	l = 0;
	while (list[l] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(list[l], STDOUT_FILENO);
		value = env_get(list[l]);
		if (value == NULL)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			break ;
		}
		else
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		l++;
	}
}

void	do_args(char *var)
{
	char	*k;
	int		pos;
	char	*var_name;
	char	*var_value;

	k = ft_strchr(var, '=');
	if (k == NULL)
	{
		if (strs_in_list(var, g_data.to_export) == 0)
			strs_append(&g_data.to_export, ft_strdup(var));
		return ;
	}
	pos = 0;
	while (var[pos] != '=')
		pos++;
	var_name = ft_substr(var, 0, pos);
	var_value = ft_substr(var, pos + 1, ft_strlen(var) - (pos + 1));
	if (strs_in_list(var_name, g_data.to_export) == 0)
		strs_append(&g_data.to_export, ft_strdup(var_name));
	env_set(var_name, var_value);
	free(var_name);
	free(var_value);
}

int	export(char **args)
{
	int	i;

	i = 1;
	if (strs_size(args) == 1)
	{
		if (sort(&g_data.to_export) == 1)
			return (1);
		write_list(g_data.to_export);
	}
	else
	{
		while (args[i] != NULL)
		{
			do_args(args[i]);
			i++;
		}
	}
	return (0);
}
