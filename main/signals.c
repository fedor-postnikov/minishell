/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:16:27 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/11 16:57:16 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_input(int signum)
{
	(void)signum;
	g_data.last_exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	process_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("^\\Quit: 3\n", STDOUT_FILENO);
	g_data.last_exit_status = 131;
}

void	process_interrupt(int signum)
{
	(void)signum;
	ft_putstr_fd("^C\n", STDOUT_FILENO);
	g_data.last_exit_status = 130;
}

void	signal_set_input(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &clear_input);
}

void	signal_set_execute(void)
{
	signal(SIGQUIT, &process_quit);
	signal(SIGINT, &process_interrupt);
}
