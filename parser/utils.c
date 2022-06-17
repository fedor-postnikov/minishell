/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:46:38 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/14 21:27:13 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Mallocs and returns token object
*/
void	*create_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	return ((void *) token);
}

/*	Checks if given char is a part of operator (<<, >>, | etc.) token
*/
int	is_operator(char c)
{
	if (c == CHAR_LESS || c == CHAR_GREAT || c == CHAR_PIPE)
		return (1);
	return (0);
}

/*	Initialize data structure for tokenizer
*/
t_tokenizer	*tokenizer_init(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	tokenizer->i = 0;
	tokenizer->input = input;
	tokenizer->state = STATE_GENERAL;
	tokenizer->token_list = NULL;
	tokenizer->token_start = 0;
	return (tokenizer);
}

void	token_trim_spaces(void *v_token)
{
	t_token		*token;
	char		*new_value;

	token = (t_token *)v_token;
	new_value = ft_strtrim(token->value, "\t ");
	free(token->value);
	token->value = new_value;
}
