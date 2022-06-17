/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:49:07 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/07 19:13:44 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (((9 <= c) && (c <= 13)) || (c == ' '))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int				sign;
	long long int	res;

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
		if (res > 2147483647 && sign == 1)
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
		nptr++;
	}
	res *= sign;
	return ((int)res);
}
