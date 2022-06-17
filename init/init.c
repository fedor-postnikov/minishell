/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:18:09 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/15 08:54:17 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Copies envp from main to local global envp.
	Also fills to_export list with variable names.
*/
void	env_init(char **envp)
{
	int	len;
	int	i;
	int	k;

	g_data.envp = strs_copy(envp);
	i = 0;
	len = strs_size(envp);
	while (i < len)
	{
		k = 0;
		while (g_data.envp[i][k] != '=' && g_data.envp[i][k] != '\0')
			k++;
		if (k == '\0')
			break ;
		strs_append(&g_data.to_export, ft_substr(g_data.envp[i], 0, k));
		i++;
	}
}

/*	Setup terminal to do not echo control signals
*/
void	term_init(void)
{
	struct termios	t;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
}

void	init_all(char **envp)
{
	term_init();
	env_init(envp);
	g_data.tmp_files_counter = 0;
}
