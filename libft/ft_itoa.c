/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:52:17 by dalfredi          #+#    #+#             */
/*   Updated: 2021/11/07 19:28:36 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_is_valid(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

static void	ft_output(int nb, char *base, int length, char *output)
{
	int	remainder;

	remainder = nb % length;
	remainder *= -1;
	nb /= length;
	if (nb != 0)
		ft_output(nb, base, length, output + 1);
	if (nb == 0)
		output[1] = 0;
	*output = *(base + remainder);
}

static void	ft_reverse_string(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (j < i / 2)
	{
		c = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = c;
		j++;
	}
}

static void	ft_putnbr_base(int nb, char *base, char *output)
{
	int		length;

	length = ft_base_is_valid(base);
	if (!length)
		return ;
	if (nb < 0)
	{
		*output = '-';
		output++;
	}
	else
		nb = -nb;
	ft_output(nb, base, length, output);
	ft_reverse_string(output);
}

char	*ft_itoa(int n)
{
	char	*res;
	char	buffer[256];
	size_t	size;

	ft_putnbr_base(n, "0123456789", buffer);
	size = ft_strlen(buffer);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, buffer, size + 1);
	return (res);
}
