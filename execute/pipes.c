/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:06:24 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/12 15:03:37 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_command_fds(void *v_cmd)
{
	t_command	*cmd;

	cmd = (t_command *)v_cmd;
	if (cmd->fd[IN] != STDIN_FILENO)
		close(cmd->fd[IN]);
	if (cmd->fd[OUT] != STDOUT_FILENO)
		close(cmd->fd[OUT]);
}

static void	set_command_fds(void *v_cmd, int fd_in, int fd_out)
{
	t_command	*cmd;

	cmd = (t_command *)v_cmd;
	cmd->fd[IN] = fd_in;
	cmd->fd[OUT] = fd_out;
}

void	pipes_create_all(void)
{
	t_list	*cmd;
	int		fd[2];
	int		prev_fd_in;

	prev_fd_in = STDIN_FILENO;
	cmd = g_data.command_list;
	while (cmd->next != NULL)
	{
		pipe(fd);
		set_command_fds(cmd->content, prev_fd_in, fd[OUT]);
		prev_fd_in = fd[IN];
		cmd = cmd->next;
	}
	set_command_fds(cmd->content, prev_fd_in, STDOUT_FILENO);
}

void	pipes_close_all(void)
{
	ft_lstiter(g_data.command_list, &close_command_fds);
}

void	set_command_pipes(t_command *cmd)
{
	dup2(cmd->fd[IN], STDIN_FILENO);
	dup2(cmd->fd[OUT], STDOUT_FILENO);
}
