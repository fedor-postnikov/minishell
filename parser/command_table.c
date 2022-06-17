/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:28:40 by dalfredi          #+#    #+#             */
/*   Updated: 2022/05/29 22:57:42 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*syntax_error(char *near_token, t_table_builder *t)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(near_token, 2);
	ft_putstr_fd("'\n", 2);
	ft_lstclear(&t->command_list, &command_delete);
	command_delete(t->cmd);
	t->cmd = NULL;
	g_data.last_exit_status = 2;
	return (NULL);
}

/*	Adds redirect to command object and checks for syntax error
*/
int	command_add_redirect(t_list **redirect_list, int redirect_type,
							t_list	*token, t_table_builder *t)
{
	char	*filename;
	int		token_type;
	char	*token_value;

	if (token->next == NULL)
	{
		syntax_error("newline", t);
		return (1);
	}
	token_get_value(token->next->content, &token_type, &token_value);
	if (token_is_operator(token_type))
	{
		syntax_error(token_value, t);
		return (1);
	}
	filename = ft_strdup(token_value);
	ft_lstadd_back(
		redirect_list, ft_lstnew(create_redirect(redirect_type, filename)));
	return (0);
}

/*	Updates t_command contents depending on token type
*/
int	token_add_to_command(t_list **token, t_table_builder *t)
{
	if (token_is_redirect(t->tok_type))
	{
		if (command_add_redirect(
				&t->cmd->redirect_list, t->tok_type, *token, t) != 0)
			return (0);
		*token = (*token)->next;
		if (*token == NULL)
			return (1);
	}
	else if (t->tok_type == TOKEN)
		strs_append(&t->cmd->args, ft_strdup(t->tok_value));
	else if (t->tok_type == PIPE)
	{
		if (t->cmd->args != NULL)
			t->cmd->name = t->cmd->args[0];
		else
		{
			syntax_error(t->tok_value, t);
			return (0);
		}
		ft_lstadd_back(&t->command_list, ft_lstnew(t->cmd));
		t->cmd = create_command(NULL, NULL, NULL, NULL);
	}
	return (1);
}

/*	Initializes variables needed for table builder
*/
void	init_table(t_table_builder *t)
{
	t->command_list = NULL;
	t->cmd = create_command(NULL, NULL, NULL, NULL);
}

/*	Main table builder function.
	Gets tokens list and returns list of commands
	with all redirect and arguments.
*/
t_list	*build_command_table(t_list *token)
{
	t_table_builder	t;

	if (token == NULL)
		return (NULL);
	init_table(&t);
	while (token != NULL)
	{
		token_get_value(token->content, &t.tok_type, &t.tok_value);
		if (token_add_to_command(&token, &t) == 0)
			return (NULL);
		if (token == NULL)
			break ;
		token = token->next;
	}
	if (t.cmd->args != NULL)
		t.cmd->name = t.cmd->args[0];
	else if (t.cmd->redirect_list == NULL)
		return (syntax_error(t.tok_value, &t));
	ft_lstadd_back(&t.command_list, ft_lstnew(t.cmd));
	return (t.command_list);
}
