/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:00:34 by dalfredi          #+#    #+#             */
/*   Updated: 2022/05/29 20:19:49 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Create new string by joining two other. Free both source string.
*/
static char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

/*	Finds in envp and returns variables value.
	Returns empty string ("") if variable not present in envp.
*/
char	*get_variable(char *source, int start, int len)
{
	char	*name;
	char	*value;

	name = ft_substr(source, start, len);
	value = env_get(name);
	if (value == NULL)
		value = ft_strdup("");
	else
		value = ft_strdup(env_get(name));
	free(name);
	return (value);
}

/*	Finds variable name, searchs it in enviroment variables
	and creates new string where variable name expands to its value.
	If variable is not initialized expands it to empty string ("").
	If dollar sign is not followed by a variable name does nothing.
*/
int	expand_dollar(t_tokenizer *tok)
{
	char	*new_str;
	char	*tmp_str;
	int		len;

	len = tok->i + 1;
	while ((ft_isalnum(tok->input[len]) || tok->input[len] == '_') \
		&& tok->input[len] != '\0')
		len++;
	if (len - (tok->i + 1) == 0 && tok->input[(tok->i + 1)] != '?')
		return (0);
	new_str = ft_substr(tok->input, 0, tok->i);
	len -= tok->i + 1;
	if ((len == 0) && tok->input[(tok->i + 1)] == '?')
	{
		tmp_str = get_exit_status();
		len = 1;
	}
	else
		tmp_str = get_variable(tok->input, tok->i + 1, len);
	new_str = strjoin_free(new_str, tmp_str);
	tmp_str = ft_substr(tok->input, tok->i + len + 1,
			ft_strlen(tok->input) - (tok->i + len + 1));
	new_str = strjoin_free(new_str, tmp_str);
	tok->input = new_str;
	return (1);
}

/*	Replaces token string with new string
	where quote on a position tok->i is deleted.
*/
void	delete_quote(t_tokenizer *tok, t_token *token)
{
	char	*str1;
	char	*str2;
	char	*new_str;

	str1 = ft_substr(token->value, 0, tok->i);
	str2 = ft_substr(token->value, tok->i + 1, \
			ft_strlen(token->value) - tok->i - 1);
	new_str = ft_strjoin(str1, str2);
	tok->i--;
	free(str1);
	free(str2);
	free(token->value);
	token->value = new_str;
	tok->input = token->value;
}
