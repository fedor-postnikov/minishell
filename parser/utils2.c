/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:38:51 by dalfredi          #+#    #+#             */
/*   Updated: 2022/05/29 19:24:41 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Mallocs and returns command object
*/
void	*create_command(char *name, char **args,
						char **envp, t_list *redirect_list)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->name = name;
	command->args = args;
	command->envp = envp;
	command->redirect_list = redirect_list;
	return (command);
}

/*	Mallocs and returns redirect object
*/
void	*create_redirect(int type, char *filename)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = type;
	redirect->filename = filename;
	return ((void *) redirect);
}

void	token_delete(void *v_token)
{
	t_token	*token;

	token = (t_token *)v_token;
	if (token->value != NULL)
	{
		free(token->value);
		token->value = NULL;
	}
	if (v_token != NULL)
		free(v_token);
}

void	token_delete_empty(t_list **lst, void (*del)(void *))
{
	t_list	*new_list;
	t_list	*iter;
	t_token	*token;

	new_list = NULL;
	iter = *lst;
	while (iter != NULL)
	{
		token = (t_token *)iter->content;
		if (token->value[0] != '\0')
		{
			ft_lstadd_back(&new_list,
				ft_lstnew(create_token(token->type, ft_strdup(token->value))));
		}
		iter = iter->next;
	}
	ft_lstclear(lst, del);
	*lst = new_list;
}

/*	Return pointers to token type and value.
*/
void	token_get_value(void *v_token, int *type, char **value)
{
	t_token	*token;

	token = (t_token *)v_token;
	*type = token->type;
	*value = token->value;
}
