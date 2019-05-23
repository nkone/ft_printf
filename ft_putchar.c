/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:44:54 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/20 14:41:00 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the character c to the standard output.
*/

#include "libft.h"

ssize_t	ft_putchar(char c)
{
	return ft_putchar_fd(c, 1);
}
