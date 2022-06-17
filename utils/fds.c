/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:20:41 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/10 17:13:39 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Error specifies in which function error occurs
*/
int	func_error(char *func_name)
{
	ft_putstr_fd("minishell :", STDERR_FILENO);
	ft_putstr_fd(func_name, STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_data.last_exit_status = 127;
	return (4);
}

static void	fd_close(int fd)
{
	if (close(fd) == -1)
		exit(func_error("close"));
}

/*	Close both fds in fd[2]
*/
void	fds_close(int fds[2])
{
	fd_close(fds[IN]);
	fd_close(fds[OUT]);
}

void	fds_save_standard(int fds[2])
{
	fds[IN] = dup(STDIN_FILENO);
	fds[OUT] = dup(STDOUT_FILENO);
}

void	fds_restore_standard(int fds[2])
{
	dup2(fds[IN], STDIN_FILENO);
	dup2(fds[OUT], STDOUT_FILENO);
	fds_close(fds);
}
