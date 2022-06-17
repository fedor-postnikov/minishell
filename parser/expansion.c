/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:03:56 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/17 15:32:45 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	switch_general(char curr_char, t_tokenizer *tok, t_token *token)
{
	if (curr_char == CHAR_QUOTE)
	{
		tok->state = STATE_QUOTE;
		delete_quote(tok, token);
	}
	else if (curr_char == CHAR_DQUOTE)
	{
		tok->state = STATE_DQUOTE;
		delete_quote(tok, token);
	}
	else if (curr_char == CHAR_DOLLAR)
	{
		if (expand_dollar(tok) == 1)
			free(token->value);
		token->value = tok->input;
	}
}

static void	switch_dquote(char curr_char, t_tokenizer *tok, t_token *token)
{
	if (curr_char == CHAR_DQUOTE)
	{
		tok->state = STATE_GENERAL;
		delete_quote(tok, token);
	}
	else if (curr_char == CHAR_DOLLAR)
	{
		if (expand_dollar(tok) == 1)
			free(token->value);
		token->value = tok->input;
	}
	if (tok->input[tok->i] == CHAR_DQUOTE)
	{
		tok->state = STATE_GENERAL;
		delete_quote(tok, token);
	}
}

static void	switch_quote(char curr_char, t_tokenizer *tok, t_token *token)
{
	if (curr_char == CHAR_QUOTE)
	{
		tok->state = STATE_GENERAL;
		delete_quote(tok, token);
	}
}

/*	Iterate over all characters in token string and perform different behavior
	depending on whether the character is inside or outside the quotes.
	Quotes are considered correct.
	If not inside any quotes or inside double quotes expand
	variable if dollar sign is encountered.
*/
static void	expand(void *v_token)
{
	t_token		*token;
	t_tokenizer	*tok;
	char		curr_char;

	token = (t_token *)v_token;
	tok = tokenizer_init(token->value);
	while (tok->i <= ft_strlen(tok->input))
	{
		curr_char = tok->input[tok->i];
		if (tok->state == STATE_GENERAL)
			switch_general(curr_char, tok, token);
		else if (tok->state == STATE_QUOTE)
			switch_quote(curr_char, tok, token);
		else if (tok->state == STATE_DQUOTE)
			switch_dquote(curr_char, tok, token);
		tok->i++;
	}
	free(tok);
}

/*	Iterate over token list to expand variables
*/
void	expand_variables(t_list *tokens)
{
	ft_lstiter(tokens, &expand);
}
