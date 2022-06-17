/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:27 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/17 17:01:01 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	exit_builtin_wrapper_main(void)
{
	char	**args;

	args = NULL;
	strs_append(&args, "0");
	exit_builtin(args);
}

void	main_loop(void)
{
	char	*input;
	t_list	*command_table;

	input = NULL;
	while (1)
	{
		g_data.heredoc_fails = 0;
		signal_set_input();
		input = get_line();
		if (input == NULL)
			exit_builtin_wrapper_main();
		command_table = parse(input);
		if (command_table == NULL)
			continue ;
		execute(command_table);
		ft_lstclear(&command_table, &command_delete);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_all(envp);
	main_loop();
}
