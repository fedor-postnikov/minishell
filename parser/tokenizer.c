/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:47:17 by dalfredi          #+#    #+#             */
/*   Updated: 2022/05/29 20:27:32 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Addes operator to token list based on two known characters */
static int	add_operator(char c1, char c2, t_list *token_list)
{
	if (c1 == CHAR_LESS && c2 != CHAR_LESS)
		ft_lstadd_back(&token_list,
			ft_lstnew(create_token(REDIR_INPUT, ft_strdup("<"))));
	else if (c1 == CHAR_GREAT && c2 != CHAR_GREAT)
		ft_lstadd_back(&token_list,
			ft_lstnew(create_token(REDIR_OUTPUT, ft_strdup(">"))));
	else if (c1 == CHAR_PIPE)
		ft_lstadd_back(&token_list,
			ft_lstnew(create_token(PIPE, ft_strdup("|"))));
	else if (c1 == c2)
	{
		if (c1 == CHAR_LESS)
			ft_lstadd_back(&token_list,
				ft_lstnew(create_token(REDIR_DELIMITER, ft_strdup("<<"))));
		else if (c1 == CHAR_GREAT)
			ft_lstadd_back(&token_list,
				ft_lstnew(create_token(REDIR_OUTPUT_APPEND, ft_strdup(">>"))));
		return (1);
	}
	return (0);
}

/* Actions to perform if tokenizer in state==STATE_GENERAL */
static void	switch_general(t_tokenizer *t, char curr_char)
{
	char	*token_str;

	if (curr_char == '\0')
	{
		token_str = ft_substr(t->input, t->token_start, t->i - t->token_start);
		ft_lstadd_back(&t->token_list,
			ft_lstnew(create_token(TOKEN, token_str)));
	}
	else if (curr_char == CHAR_QUOTE)
		t->state = STATE_QUOTE;
	else if (curr_char == CHAR_DQUOTE)
		t->state = STATE_DQUOTE;
	else if (is_operator(curr_char) || curr_char == ' ')
	{
		token_str = ft_substr(t->input, t->token_start, t->i - t->token_start);
		ft_lstadd_back(&t->token_list,
			ft_lstnew(create_token(TOKEN, token_str)));
		t->i += add_operator(t->input[t->i], t->input[t->i + 1], t->token_list);
		if (t->i >= ft_strlen(t->input))
			return ;
		t->token_start = t->i + 1;
	}
}

/*	Show error, free allocated memory and return NULL
*/
void	*return_error(t_tokenizer *tok)
{
	ft_putendl_fd("minishell: parse error: unclosed quote",
		STDERR_FILENO);
	ft_lstclear(&tok->token_list, &token_delete);
	free(tok);
	g_data.last_exit_status = 2;
	return (NULL);
}

/*	This function return list of tokens in following format:
	struct s_token {
		int 	type,
		char	*value
	};
	The types of token are as follows:
		[command or filename] -- TOKEN ,
		"<"  -- REDIR_INPUT,
		">"  -- REDIR_OUTPUT,
		">>" -- REDIR_OUTPUT_APPEND,
		"<<" -- REDIR_DELIMITER,
		"|"  -- PIPE
	The functionality is implemented using a finite state machine.
 */
t_list	*tokenize(char *input)
{
	t_list		*token_list;
	char		curr_char;
	t_tokenizer	*tok;

	tok = tokenizer_init(input);
	while (tok->i <= ft_strlen(input))
	{
		curr_char = input[tok->i];
		if (tok->state == STATE_GENERAL)
			switch_general(tok, curr_char);
		else if (tok->state == STATE_QUOTE && curr_char == CHAR_QUOTE)
			tok->state = STATE_GENERAL;
		else if (tok->state == STATE_DQUOTE && curr_char == CHAR_DQUOTE)
			tok->state = STATE_GENERAL;
		tok->i++;
	}
	if (tok->state != STATE_GENERAL)
		return ((return_error(tok)));
	token_list = tok->token_list;
	free(tok);
	return (token_list);
}
