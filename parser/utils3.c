/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:36:51 by dalfredi          #+#    #+#             */
/*   Updated: 2022/05/29 19:25:22 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_operator(int token_type)
{
	if (token_type > 0)
		return (1);
	return (0);
}

int	token_is_redirect(int token_type)
{
	if (token_type == REDIR_INPUT || token_type == REDIR_OUTPUT
		|| token_type == REDIR_OUTPUT_APPEND
		|| token_type == REDIR_DELIMITER)
		return (1);
	return (0);
}

void	redirect_delete(void *v_redirect)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)v_redirect;
	if (redirect->filename != NULL)
	{
		free(redirect->filename);
		redirect->filename = NULL;
	}
	if (v_redirect != NULL)
		free(v_redirect);
}

void	command_delete(void *v_command)
{
	t_command	*command;

	command = (t_command *)v_command;
	strs_free(&command->args);
	strs_free(&command->envp);
	ft_lstclear(&command->redirect_list, &redirect_delete);
	if (v_command != NULL)
		free(v_command);
}
