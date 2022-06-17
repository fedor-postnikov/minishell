/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:23:18 by bpono             #+#    #+#             */
/*   Updated: 2022/06/14 18:18:10 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *name)
{
	if (ft_isdigit(name[0]) == 1)
		return (1);
	return (0);
}

int	unset(char **list)
{
	int		i;

	if (strs_size(list) < 2)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (list[i] != NULL)
	{
		if (check_name(list[i]) == 1)
		{
			ft_putstr_fd("bash: unset: ", 2);
			ft_putstr_fd(list[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		else
		{
			env_delete(list[i]);
			strs_delete(&g_data.to_export, list[i]);
		}
		i++;
	}
	return (0);
}
