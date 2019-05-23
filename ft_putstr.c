/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:13:34 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/20 14:40:50 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the string s to standard output
*/

#include "libft.h"

ssize_t	ft_putstr(char const *s)
{
	if (s)
		return ft_putstr_fd(s, 1);
	return (-1);
}
