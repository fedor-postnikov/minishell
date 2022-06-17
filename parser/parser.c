/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:01:34 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/17 16:40:54 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Main parsing function.
	Gets string with raw user input	and
	builds a table of parsed commands
	with redirects and arguments for each command (pipeline).
	Throws a syntax error (e.g. unclosed quote) if any.
*/
t_list	*parse(char *input)
{
	t_list	*tokens;
	t_list	*command_table;
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, "\r\t ");
	input = trimmed_input;
	tokens = tokenize(input);
	token_delete_empty(&tokens, &token_delete);
	free(trimmed_input);
	if (tokens == NULL)
		return (NULL);
	expand_variables(tokens);
	command_table = build_command_table(tokens);
	ft_lstclear(&tokens, &token_delete);
	return (command_table);
}
