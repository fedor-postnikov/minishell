/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpono <bpono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:52:58 by bpono             #+#    #+#             */
/*   Updated: 2022/06/15 17:58:02 by bpono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (strs_size(args) > 1)
	{
		while (ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
		{
			n = 1;
			i++;
		}
		while ((ft_strcmp(args[i], " ") == 0))
			i++;
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
