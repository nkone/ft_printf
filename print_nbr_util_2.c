/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:47:34 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/22 19:47:34 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	flag_to_index(int flag)
{
	int i;

	i = 0;
	while (flag)
	{
		flag >>= 1;
		i++;
		if (!flag)
			break;
	}
	return (i);
}

int	get_nbr_len(uintmax_t n)
{
	int len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	print_uintmax(uintmax_t n)
{
	if (n >= 10)
	{
		print_uintmax(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n % 10 + '0');
}
