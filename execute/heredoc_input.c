/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:17:48 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/12 21:15:38 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_tmp_file(char **filename)
{
	int		fd;
	char	*tmp_filename;
	char	*tmp_file_number;

	tmp_file_number = ft_itoa(g_data.tmp_files_counter);
	tmp_filename = ft_strjoin(TMP_FILENAME, tmp_file_number);
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		func_error("open");
	free(tmp_file_number);
	*filename = tmp_filename;
	g_data.tmp_files_counter++;
	return (fd);
}

static void	heredoc_interrupt(int signal)
{
	(void)signal;
	g_data.last_exit_status = 130;
	write(1, "\n", 1);
	exit(130);
}

static	void	write_input_to_file(int tmp_file, char *delimiter)
{
	char	*input;

	signal(SIGINT, heredoc_interrupt);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n",
				STDERR_FILENO);
			close(tmp_file);
			exit(0);
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			close(tmp_file);
			free(input);
			break ;
		}
		ft_putendl_fd(input, tmp_file);
		free(input);
	}
	exit(0);
}

static void	replace_heredoc(t_redirect *redirect, char *filename)
{
	free(redirect->filename);
	redirect->filename = filename;
	redirect->type = REDIR_INPUT;
}

void	heredoc_input(t_redirect *redirect)
{
	int		tmp_file;
	char	*tmp_filename;
	pid_t	pid;
	int		exit_status;

	if (g_data.heredoc_fails == 1)
	{
		redirect->type = REDIR_ERROR;
		return ;
	}
	tmp_file = create_tmp_file(&tmp_filename);
	if (tmp_file == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		write_input_to_file(tmp_file, redirect->filename);
	waitpid(pid, &exit_status, 0);
	close(tmp_file);
	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 130)
	{
		heredoc_clean_up(redirect, tmp_filename);
		return ;
	}
	replace_heredoc(redirect, tmp_filename);
}
