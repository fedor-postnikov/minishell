/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:59:11 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/15 11:05:26 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Return exit code 1 on error
*/
static int	open_error(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_data.last_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

static int	redir_output(char *filename, int open_flags)
{
	int	fd;

	fd = open(filename, open_flags, 0644);
	if (fd == -1)
		return (open_error(filename));
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	redir_input(char *filename, int open_flags)
{
	int	fd;

	fd = open(filename, open_flags);
	if (fd == -1)
		return (open_error(filename));
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

/*	Choose what redirect to perform
	If type==REDIR_ERROR it means heredoc previously
	was interrupted by SIGINT, so exit
*/
static void	make_redirect(void *v_redirect)
{
	t_redirect	*redirect;
	int			status;

	if (g_data.redirect_fails == 1)
		return ;
	redirect = (t_redirect *)v_redirect;
	status = 0;
	if (redirect == NULL)
		return ;
	if (redirect->type == REDIR_INPUT)
		status = redir_input(redirect->filename, O_RDONLY);
	else if (redirect->type == REDIR_OUTPUT)
		status = redir_output(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirect->type == REDIR_OUTPUT_APPEND)
		status = redir_output(
				redirect->filename, O_WRONLY | O_CREAT | O_APPEND);
	else if (redirect->type == REDIR_ERROR)
		return ;
	if (status != 0)
		g_data.redirect_fails = 1;
}

/*	Iterate over redirect list and perform redirection
*/
void	make_redirects(t_list *redirect_list)
{
	if (redirect_list != NULL)
		ft_lstiter(redirect_list, &make_redirect);
}
