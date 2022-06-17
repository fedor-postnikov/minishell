/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:02:21 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/16 18:01:17 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	if (((9 <= c) && (c <= 13)) || (c == ' '))
		return (1);
	return (0);
}

int	return_numeric_error(const char *nbr)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, nbr, ft_strlen(nbr));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

int	ft_atoi_long(const char *nptr, char *str)
{
	int						sign;
	unsigned long long int	res;

	while (is_space(*nptr))
		nptr++;
	sign = 1;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	res = 0;
	while (('0' <= *nptr) && (*nptr <= '9'))
	{
		res *= 10;
		res += *nptr - '0';
		if (res > 9223372036854775807 && sign == 1)
			return (return_numeric_error(str));
		if (res > 9223372036854775808ULL && sign == -1)
			return (return_numeric_error(str));
		nptr++;
	}
	res *= sign;
	return ((long long int)res);
}

void	check_if_argument_numeric(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '-')
		i += 1;
	if (code[i] == '\0')
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: -: numeric argument required\n", 46);
		exit(255);
	}
	while (ft_isdigit(code[i]) == 1)
		i += 1;
	if (code[i] != '\0')
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 17);
		write(2, code, ft_strlen(code));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
}

void	exit_builtin(char **code)
{
	unsigned char	exit_code;

	if (code[1] == NULL)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	check_if_argument_numeric(code[1]);
	exit_code = ft_atoi_long(code[1], code[1]);
	if (code[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	write(2, "exit\n", 5);
	exit(exit_code);
}
