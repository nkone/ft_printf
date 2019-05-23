/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:52:04 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/22 20:28:30 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:45:13 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/22 18:43:07 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"

# define _F_MINUS	(1U << 0U)
# define _F_PLUS	(1U << 1U)
# define _F_SPACE	(1U << 2U)
# define _F_ZERO	(1U << 3U)
# define _F_HASH	(1U << 4U)

# define _F_PCN		(1U << 5U)

# define _S_H		(1U << 0U)
# define _S_HH		(1U << 1U)
# define _S_L		(1U << 2U)
# define _S_LL		(1U << 3U)
# define _S_LF		(1U << 4U)
# define _S_Z		(1U << 5U)
# define _S_J		(1U << 6U)
# define _S_T		(1U << 7U)

# define _VALID_TYPES "cs%dipouxXf"

typedef struct		s_print
{
	unsigned int	argv;
	unsigned int	flag;
	int				pcn;
	unsigned int	size;
	unsigned int	type;
	int				width;
	unsigned int	done;
	const char		*str;
	va_list			ap;
}					t_print;

void				print_char(t_print *p);
void				print_str(t_print *p);
void				print_mod(t_print *p);
void				print_nbr(t_print *p);

typedef void		t_jump(t_print *p);

static	t_jump *g_print_table[] =
{
	print_char,
	print_str,
	print_mod,
	print_nbr,
	print_nbr
};

intmax_t			print_nbr_nosize(t_print *p);
intmax_t			print_nbr_sizeh(t_print *p);	
intmax_t			print_nbr_sizehh(t_print *p);	
intmax_t			print_nbr_sizel(t_print *p);	
intmax_t			print_nbr_sizell(t_print *p);	
intmax_t			print_nbr_sizelf(t_print *p);
intmax_t			print_nbr_sizej(t_print *p);
intmax_t			print_nbr_sizez(t_print *p);
intmax_t			print_nbr_sizet(t_print *p);

typedef intmax_t	t_getsize(t_print *p);

static	t_getsize *g_signed_tab[] =
{
	print_nbr_nosize,
	print_nbr_sizeh,
	print_nbr_sizehh,
	print_nbr_sizel,
	print_nbr_sizell,
	print_nbr_sizelf,
	print_nbr_sizej,
	print_nbr_sizez,
	print_nbr_sizet
};

intmax_t			print_nbr_nosize_arg(va_list ap);
intmax_t			print_nbr_sizeh_arg(va_list ap);	
intmax_t			print_nbr_sizehh_arg(va_list ap);	
intmax_t			print_nbr_sizel_arg(va_list ap);	
intmax_t			print_nbr_sizell_arg(va_list ap);	
intmax_t			print_nbr_sizelf_arg(va_list ap);
intmax_t			print_nbr_sizej_arg(va_list ap);
intmax_t			print_nbr_sizez_arg(va_list ap);
intmax_t			print_nbr_sizet_arg(va_list ap);

typedef	intmax_t	t_getsizearg(va_list ap);

static t_getsizearg *g_signed_tab_arg[] =
{
	print_nbr_nosize_arg,
	print_nbr_sizeh_arg,
	print_nbr_sizehh_arg,
	print_nbr_sizel_arg,
	print_nbr_sizell_arg,
	print_nbr_sizelf_arg,
	print_nbr_sizej_arg,
	print_nbr_sizet_arg
};


/*
** ft_printf_util.c
*/

void				reset_print(t_print *p);
void				reset_collector(t_print *p);
int					put_nchar(char c, int n);
int					get_nspace(t_print *p,	int len);

/*
** print_nbr_diver.c
*/

void				print_nbr_case1(t_print *p, intmax_t n);
void				print_nbr_case2(t_print *p, intmax_t n, int sp);
void				print_nbr_case3(t_print *p, intmax_t n, int pads);
void				print_nbr_case4(t_print *p, intmax_t n, int sp, int pads);
void				print_nbr_driver(t_print *p, intmax_t n, int sp, int pads);

/*
** print_nbr_util_1.c
*/

int					print_nbr_plus_flag(intmax_t n);
int					print_nbr_sp_flag(intmax_t n);
int					get_nbr_space(t_print *p, intmax_t n, int pads);	
void				process_sp_plus_flag(t_print *p, intmax_t n);
void				print_nbr_prototype(t_print *p, intmax_t n);

/*
** print_nbr_util_2.c
*/

int					flag_to_index(int flag);
int					get_nbr_len(uintmax_t n);
void				print_uintmax(uintmax_t n);

#endif
