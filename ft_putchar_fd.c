/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:50:36 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/20 14:41:25 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the char c to the file descriptor fd
*/

#include "libft.h"

ssize_t		ft_putchar_fd(char c, int fd)
{
	return write(fd, &c, 1);
}
