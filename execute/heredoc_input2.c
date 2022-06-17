/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:01:50 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/12 21:11:59 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_all_heredocs(void	*v_command)
{
	t_command	*command;
	t_list		*redir;
	t_redirect	*redirect;

	command = (t_command *)v_command;
	redir = command->redirect_list;
	while (redir != NULL)
	{
		redirect = (t_redirect *)redir->content;
		if (redirect->type == REDIR_DELIMITER)
			heredoc_input(redirect);
		redir = redir->next;
	}
}

void	delete_tmp_files(void	*v_command)
{
	t_command	*command;
	t_list		*redir;
	t_redirect	*redirect;

	command = (t_command *)v_command;
	redir = command->redirect_list;
	while (redir != NULL)
	{
		redirect = (t_redirect *)redir->content;
		if (redirect->type == REDIR_INPUT && \
			ft_strncmp(
				redirect->filename, TMP_FILENAME, ft_strlen(TMP_FILENAME)) == 0)
		{
			if (unlink(redirect->filename) == -1)
				func_error("unlink");
		}
		redir = redir->next;
	}
}

void	heredoc_clean_up(t_redirect *redirect, char *tmp_filename)
{
	redirect->type = REDIR_ERROR;
	if (unlink(tmp_filename) == -1)
		func_error("unlink");
	free(tmp_filename);
	g_data.heredoc_fails = 1;
	g_data.last_exit_status = 130;
}
