/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpono <bpono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:06:00 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/15 20:52:31 by bpono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (cmd_name == NULL)
		return (0);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	return (0);
}

int	builtin_start(t_command *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(cmd->name, "exit") == 0)
		exit_builtin(cmd->args);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		exit_status = echo(cmd->args);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		exit_status = cd(cmd->args);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		exit_status = pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		exit_status = export(cmd->args);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		exit_status = unset(cmd->args);
	else if (ft_strcmp(cmd->name, "env") == 0)
		exit_status = env(g_data.envp);
	return (exit_status);
}

void	builtin_execute(t_command *cmd)
{
	int		exit_status;

	exit_status = builtin_start(cmd);
	if (cmd->fd[IN] != STDIN_FILENO)
		close(cmd->fd[IN]);
	if (cmd->fd[OUT] != STDOUT_FILENO)
		close(cmd->fd[OUT]);
	cmd->pid = -1;
	g_data.last_exit_status = exit_status;
}
