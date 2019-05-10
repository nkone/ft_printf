/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:45:13 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/09 20:04:56 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define _F_MINUS	(1U << 0U)
# define _F_PLUS	(1U << 1U)
# define _F_SPACE	(1U << 2U)
# define _F_ZERO	(1U << 3U)
# define _F_HASH	(1U << 4U)

# define _S_H		(1U << 0U)
# define _S_HH		(1U << 1U)
# define _S_L		(1U << 2U)
# define _S_LL		(1U << 3U)
# define _S_LF		(1U << 4U)

# define _VALID_TYPES "cs%dipouxXf"

typedef struct		s_print
{
	unsigned int	argv;
	unsigned int	flag;
	unsigned int	pcn;
	unsigned int	size;
	unsigned int	type;
	unsigned int	width;
	unsigned int	done;
	const char		*str;
	va_list			ap;
}					t_print;

void				print_char(t_print *p);
void				print_str(t_print *p);
void				print_mod(t_print *p);

typedef void		t_jump(t_print *p);

t_jump				*g_print_table[] =
{
	print_char,
	print_str,
	print_mod
};

#endif
