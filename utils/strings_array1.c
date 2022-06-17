/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_array1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:40:26 by bpono             #+#    #+#             */
/*   Updated: 2022/06/14 18:27:22 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strs_delete(char ***strs, char *str_to_delete)
{
	char	**new_strs;
	int		i;

	if (strs == NULL)
		return ;
	if (*strs == NULL)
		return ;
	new_strs = NULL;
	i = 0;
	while ((*strs)[i] != NULL)
	{
		if (ft_strcmp((*strs)[i], str_to_delete) != 0)
			strs_append(&new_strs, ft_strdup((*strs)[i]));
		i++;
	}
	strs_free(strs);
	*strs = new_strs;
}
