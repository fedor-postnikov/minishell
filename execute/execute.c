/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:22:17 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/15 11:07:30 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_error(char *cmd, char *error_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_data.last_exit_status = 127;
}

void	command_start_execve(t_command *cmd)
{
	pid_t	pid;
	char	*full_path;

	if (cmd->name == NULL)
		return ;
	pid = fork();
	signal_set_execute();
	if (pid == -1)
		func_error("fork");
	else if (pid == 0)
	{
		pipes_close_all();
		full_path = get_full_path(cmd->name);
		if (execve(full_path, cmd->args, cmd->envp) == -1)
		{
			exec_error(full_path, "command not found");
			exit(127);
		}
	}
	cmd->pid = pid;
}

void	execute_command(void *v_command)
{
	t_command	*command;
	int			std_fds[2];

	command = (t_command *)v_command;
	if (g_data.heredoc_fails == 1)
	{
		command->pid = -1;
		return ;
	}
	g_data.redirect_fails = 0;
	fds_save_standard(std_fds);
	set_command_pipes(command);
	make_redirects(command->redirect_list);
	if (g_data.redirect_fails == 1)
	{
		fds_restore_standard(std_fds);
		return ;
	}
	command->envp = strs_copy(g_data.envp);
	if (is_builtin(command->name))
		builtin_execute(command);
	else
		command_start_execve(command);
	fds_restore_standard(std_fds);
}

void	wait_child(void *v_command)
{
	t_command	*command;
	int			exit_status;

	command = (t_command *)v_command;
	if (command->pid > 0)
		waitpid(command->pid, &exit_status, 0);
	else
		return ;
	if (WIFEXITED(exit_status))
		g_data.last_exit_status = WEXITSTATUS(exit_status);
}

void	execute(t_list *command_list)
{
	g_data.command_list = command_list;
	pipes_create_all();
	ft_lstiter(command_list, &read_all_heredocs);
	ft_lstiter(command_list, &execute_command);
	pipes_close_all();
	ft_lstiter(command_list, &wait_child);
	ft_lstiter(command_list, &delete_tmp_files);
}
