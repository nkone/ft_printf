/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:41:48 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/22 20:38:28 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** -----------------------------===[SYNTAX]===--------------------------------|
** %[parameters][flags][width][.precision][size]type
*/

/*
** |---------------------------===[PARAMETERS]===------------------------------|
** |-----------+---------------------------------------------------------------|
** | Character |                          Description                          |
** |-----------+---------------------------------------------------------------|
** | [n$]      | n is the #'s of the parameter, allowing the same param to be  |
** |           | output multiple times w/ various modifers or dif orders.      |
** |           | If a placeholder specifies a parameter, the rest must follow. |
** |-----------+---------------------------------------------------------------|
** Ex. printf("%3$d %3$d, %1$d %1$ d, %2$d %2$+d", -1, 2, 3)
** Output: 3 3, -1 -1, 2 +2
*/

/*
** -----------------------------===[FLAGS]===----------------------------------|
** | Character   |                        Description                          |
** |-------------+-------------------------------------------------------------|
** | [-] (minus) | Left align the output of this place holder                  |
** | [+] (plus)  | Add '+' for positive signed numeric type ('-' for negative) |
** | [ ] (space) | Add ' ' for positive #', '-' for negative. Ignored if [+]   |
** |             | flag exists.                                                |
** | [0] (zero)  | If 'width' option is specified, prepends 0's. Default add   |
** |             | spaces.                                                     |
** | [#] (hash)  | Alternate form:                                             |
** |             | For [g,G] types, trailing 0's are NOT removed               |
** |             | For [f,F,e,E,g,G], output contains decimal point            |
** |             | For [o,x,X], 0, 0x, 0X, respectively add to non-zero #'s    |
** |-------------+-------------------------------------------------------------|
** Ex. printf("|%1$d| |%1$+d| |%1$ d| |%1$0d| |%1$03d| |%2$.2g| |%2$#g|
** 			|%2$#.0f| |%2$7.3f| |%2$-7.3f| |%3$#.0e|", 1, 21.3, 42.);
** Out:|1| |+1| | 1| |1| |001| |21| |21.3000| |21.| | 21.300| |21.300 | |4.e+01|
*/

/*
** ----------------------------===[WIDTH]===-----------------------------------|
** | Character      |                     Description                          |
** |----------------+----------------------------------------------------------|
** | [*] (asterisk) | Specifies minimum of char to the output. May be omitted  |
** |                | and also can be pass as a dynamic value using *. Can be  |
** |                | used in conjunction with 0 and -                         |
** |----------------+----------------------------------------------------------|
*/

/*
** |---------------------------===[PRECISION]===-------------------------------|
** | Character |                           Description                         |
** |-----------+:--------------------------------------------------------------|
** | [.] (dot) | Specifies maximum limit on the output. For float, it specifies|
** |           |    the #'s of digits to the right of decimal point that the   |
** |           |  output should be rounded. For string, it limits the character|
** |           |                after which should be truncated.               |
** |-----------+---------------------------------------------------------------|
*/

/*
** |-----------------------------===[SIZE]===----------------------------------|
** | Character |                           Description                         |
** |-----------+---------------------------------------------------------------|
** | [h]       | For int type, expect an int_sized arg promoted from a short   |
** | [hh]      | For int type, expect an int_sized arg promoted from a char    |
** | [l]       | For int type, expect a long arg                               |
** |           | For floats, this has no effect                                |
** | [ll]      | For int type, expect a long long arg                          |
** | [L]       | For floats type, expect an long double arg                    |
** | [z]       | For int type, expect a size_t arg                             |
** | [j]       | For int type, expect an int_max arg                           |
** | [t]       | For int type, expect a ptrdiff_t arg                          |
** |-----------+---------------------------------------------------------------|
*/

/*
** |---------------------------===[TYPES]===-----------------------------------|
** | Character |                           Description                         |
** |-----------+---------------------------------------------------------------|
** | [%]       | Prints a literal % (doesn't accept previous fields)           |
** | [d, i]    | Signed decimal int. Similar but different when use w/ scanf() |
** |           | %i is hex or octal if preceded by 0x or 0, respectively       |
** | [u]       | Unsigned decimal int.                                         |
** | [f, F]    | Double in fixed-point notation. Differs in output string for  |
** |           | an inf # or NaN (inf, infinity, nan for f)                    |
** |           | (INF, INFINITY, NAN for F)                                    |
** | [e, E]    | Double in standard form ([-]d.ddde[+/-]ddd). E uses letter E  |
** | [g, G]    | Double in in either normal or exponential notation.           |
** |           | Insignificant zeros to the right of decimal point are not     |
** |           | included. Decimal point is not included for whole numbers.    |
** | [x, X]    | Unsigned int as hex.                                          |
** | [o]       | Unsigned int octal.                                           |
** | [s]       | null-terminated string.                                       |
** | [c]       | character.                                                    |
** | [p]       | void pointer in an implementation-defined format              |
** | [a, A]    | double in hex, starting with 0x or 0X.                        |
** | [n]       | prints nothing, but writes # of chars successfully written    |
** |           | so far into integer pointer parameter.                        |
** |-----------+---------------------------------------------------------------|
*/

// To Do List:
// Learn Dispatch Table to improve coding skills and structure handling✓.
// Study Exam Questions✓;
// Create struct to collect flags ✓; 
// Create a function pointers to handle width✓;
// Collect size✓;
// Putnumber✓;
// Find p->done for nbr w/ pcn;

int	collect_argv(t_print *p)
{
	const char	*s;

	s = p->str;
	while (ft_isdigit(*s))
		s++;
	if (*s != '$')
		return (0);
	else
		p->argv = ft_atoi(p->str);
	while (ft_isdigit(*p->str))
		p->str++;
	return (1);
}
int	collect_flag(t_print *p) 
{
	if (*p->str == '-')
		return (p->flag |= _F_MINUS);
	if (*p->str == '+')
		return (p->flag |= _F_PLUS);
	if (*p->str == ' ')
		return (p->flag |= _F_SPACE);
	if (*p->str == '0')
		return (p->flag |= _F_ZERO);
	if (*p->str == '#')
		return (p->flag |= _F_HASH);	
	return (0);
}

int	collect_size(t_print *p)
{
	if (p->size)
		return (0);
	if (*p->str == 'h' && *(p->str + 1) != 'h')
		return (p->size |= _S_H);
	if (*p->str == 'h' && *(p->str++) == 'h')
		return (p->size |= _S_HH);
	if (*p->str == 'l' && *(p->str + 1) != 'l')
		return (p->size |= _S_L);
	if (*p->str == 'l' && *(p->str++) == 'l')
		return (p->size |= _S_LL);
	if (*p->str == 'L')
		return (p->size |= _S_LF);
	if (*p->str == 'z')
		return (p->size |= _S_Z);
	if (*p->str == 'j')
		return (p->size |= _S_J);
	if (*p->str == 't')
		return (p->size |= _S_T);
	return (0);
}
	
int	collect_width(t_print *p)
{
	if (ft_isdigit(*p->str))
	{
		p->width = ft_atoi(p->str);
		while (ft_isdigit(*p->str))
			p->str++;
		p->str--;
		return (1);
	}
	else if (*p->str == '*')
	{
		p->width = va_arg(p->ap, int);
		(p->width < 0) && (p->flag |= _F_MINUS);
		return (1);
	}
	return (0);
}

int	collect_pcn(t_print *p)
{
	(*p->str == '.') && (p->flag |= _F_PCN);
	(*p->str == '.') && p->str++;
	if (ft_isdigit(*p->str))
	{
		p->pcn = ft_atoi(p->str);
		while (ft_isdigit(*p->str))
			p->str++;
		p->str--;
		return (1);
	}
	else if (*p->str == '*')
		return (p->pcn = va_arg(p->ap, int));
	return (0);
}

int	collect_type(t_print *p)
{
	char *ref;

	if (p->type || !*p->str)
		return (0);
	if (!(ref = ft_strchr(_VALID_TYPES, *p->str)))
		return (0);
	else 
		return (p->type = (ptrdiff_t)(ref - _VALID_TYPES) + 1);
	return (0);
}	
	
int	collector_driver(t_print *p)
{
	(collect_argv(p)) && p->str++;
	while (collect_flag(p))
		p->str++;
	(collect_width(p)) && p->str++;
	(collect_pcn(p)) && p->str++;
	(collect_size(p)) && p->str++;
	(collect_type(p)) && p->str++;
//	printf("\nargv: %d flag: %d width: %d pcn: %d size: %d type: %d \n", p->argv, p->flag, p->width, p->pcn, p->size, p->type);
	if (!p->type)
		return (0);
	return (1);
}

void	print_char_(t_print *p, char c)
{
	char	d;

	d = (p->flag & _F_ZERO && !(p->flag & _F_MINUS)) ? '0' : ' ';
	if (!(p->flag & _F_MINUS))
		put_nchar(d, p->width-1);
	ft_putchar(c);
	if (p->flag & _F_MINUS)
		put_nchar(d, p->width-1);
}

int		get_char_argv(t_print *p)
{
	va_list		ap;
	int			tmp;
	int			c;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp-- > 0)
		c = va_arg(ap, int);
	va_end(ap);
	return (c);
}

void	print_char(t_print *p)
{
	char		c;

	c = (p->argv) ? get_char_argv(p) : va_arg(p->ap, long int);
	p->done += (p->width) ? (p->width) : 1;
	if ((p->done) >= INT_MAX)
		return;
	print_char_(p, c);
}

void	print_str_pcn(t_print *p, char *s, int space)
{
	int len;
	char c;

	c = (p->flag & _F_ZERO && !(p->flag & _F_MINUS)) ? '0' : ' ';
	len = ft_strlen(s);
	if (p->flag & _F_MINUS)
	{
		while (p->pcn-- && len--)
			ft_putchar(*s++);
		put_nchar(c, space);
	}
	else if (!(p->flag & _F_MINUS))
	{
		put_nchar(c, space);
		while (p->pcn-- && len--)
			ft_putchar(*s++);
	}
}

void	print_str_(t_print *p, char *s, int space)
{
	char c;

	c = (p->flag & _F_ZERO && !(p->flag & _F_MINUS)) ? '0' : ' ';
	(!s) &&	(s = "(null)");
	if (p->flag & _F_PCN)
		print_str_pcn(p, s, space);
	else
	{
		if (!(p->flag & _F_MINUS))
			put_nchar(c, space);
		ft_putstr(s);
		if (p->flag & _F_MINUS)
			put_nchar(c, space);
	}
}

char	*get_str_argv(t_print *p)
{
	va_list		ap;
	int			tmp;
	char		*s;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp-- > 0)
		s = va_arg(ap, char *);
	va_end(ap);
	return (s);
}	

void	print_str(t_print *p)
{
	int	space;
	int	len;
	char			*s;

	s = (p->argv) ? get_str_argv(p) : va_arg(p->ap, char *);
	len = (s) ? ft_strlen(s) : 6;
	space = get_nspace(p, len);
	if (!(p->flag & _F_PCN))
		p->done += (len + space);
	else if (p->flag & _F_PCN)
		p->done += (p->pcn > len) ? (len + space) : (p->pcn + space);
	if ((p->done) >= INT_MAX)
		return;
	print_str_(p, s, space);
}

void	print_mod(t_print *p)
{
	p->done += (p->width) ? (p->width) : 1;
	print_char_(p, '%');
}

intmax_t	print_nbr_nosize(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, int);
	return (n);
}

intmax_t	print_nbr_nosize_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, int);
	return (n);
}

intmax_t	print_nbr_sizeh(t_print *p)
{
	intmax_t n;
	
	n = (short)(va_arg(p->ap, int));
	return (n);
}

intmax_t	print_nbr_sizeh_arg(va_list ap)
{
	intmax_t n;

	n = (short)va_arg(ap, int);
	return (n);
}

intmax_t	print_nbr_sizehh(t_print *p)
{
	intmax_t n;

	n = (char)(va_arg(p->ap, int));
	return (n);
}

intmax_t	print_nbr_sizehh_arg(va_list ap)
{
	intmax_t n;

	n = (char)(va_arg(ap, int));
	return (n);
}

intmax_t	print_nbr_sizel(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, long int);
	return (n);
}

intmax_t	print_nbr_sizel_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, long int);
	return (n);
}

intmax_t	print_nbr_sizell(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, long long int);
	return (n);
}

intmax_t	print_nbr_sizell_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, long long int);
	return (n);
}

intmax_t	print_nbr_sizelf(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, int);
	return (n);
}

intmax_t	print_nbr_sizelf_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, int);
	return (n);
}

intmax_t	print_nbr_sizej(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, intmax_t);
	return (n);
}

intmax_t	print_nbr_sizej_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, intmax_t);
	return (n);
}

intmax_t	print_nbr_sizez(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, size_t);
	return (n);
}

intmax_t	print_nbr_sizez_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, size_t);
	return (n);
}

intmax_t	print_nbr_sizet(t_print *p)
{
	intmax_t n;

	n = va_arg(p->ap, ssize_t);
	return (n);
}

intmax_t	print_nbr_sizet_arg(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, ssize_t);
	return (n);
}

intmax_t	print_nbr_getsize(t_print *p)
{
	intmax_t n;

	n = g_signed_tab[flag_to_index(p->size)](p); 
	return (n);
}

intmax_t	print_nbr_getsize_arg(t_print *p)
{
	intmax_t n;
	va_list ap;
	int		tmp;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp-- > 0)
		n = g_signed_tab_arg[flag_to_index(p->size)](ap);
	va_end(ap);
	return (n);
}

void print_nbr(t_print *p)
{
	intmax_t n;
	int len;
	int space;
	int pads;
	
	n = (p->argv) ? print_nbr_getsize_arg(p) : print_nbr_getsize(p);
	len = (n < 0) ? get_nbr_len(-n) : get_nbr_len(n);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_nbr_space(p, n, pads);
	p->done += (space + pads + len);
	if (p->done >= INT_MAX)
		return ;
	if (n < 0)
		p->done++;
	else if (n >= 0 && (p->flag & _F_PLUS || p->flag & _F_SPACE))
		p->done++;
	print_nbr_driver(p, n, space, pads);
}

int	ft_printf_con(t_print *p)
{
	if (*p->str == '%')
	{
		p->str++;
		if (!*p->str)
			return (0);
		if (!collector_driver(p))
			return (0);
		g_print_table[p->type - 1](p);
		if (p->done > INT_MAX)
			return (-1);
	}
	else
	{
		if (p->done == INT_MAX)
			return (-1);
		p->done++;
		ft_putchar(*p->str++);
	}
	return (1);
}

int	ft_printf_(const char *str, va_list ap)
{
	t_print p;
	int check;

	reset_print(&p);
	va_copy(p.ap, ap);
	p.str = str;
	while (*p.str)
	{
		reset_collector(&p);
		if (!(check = ft_printf_con(&p)))
			return (p.done);
		else if (check == -1)
			return (-1);
	}	
	va_end (p.ap);
	return (p.done);
}

int	ft_printf(const char *str, ...)
{
	va_list ap;
	int done;

	va_start (ap, str);
	done = ft_printf_(str, ap);
	va_end(ap);
	return (done);
}


int main(void)
{/*
	int n = 0;
	printf("-------------------------------------BASICS---------------------------------------\n");
	printf("For int n: %d\n", n);
	printf("ft_printf: %d vs %d :printf #1\n",ft_printf("|%d|\t", n),		printf("|%d|\t", n));
	printf("ft_printf: %d vs %d :printf #2\n",ft_printf("|%1d|\t", n),		printf("|%1d|\t", n));
	printf("ft_printf: %d vs %d :printf #3\n",ft_printf("|%2d|\t", n),		printf("|%2d|\t", n));
	printf("ft_printf: %d vs %d :printf #4\n",ft_printf("|%3d|\t", n),		printf("|%3d|\t", n));
	printf("ft_printf: %d vs %d :printf #5\n",ft_printf("|%+d|\t", n),		printf("|%+d|\t", n));
	printf("ft_printf: %d vs %d :printf #6\n",ft_printf("|%+1d|\t", n),		printf("|%+1d|\t", n));
	printf("ft_printf: %d vs %d :printf #7\n",ft_printf("|%+2d|\t", n),		printf("|%+2d|\t", n));
	printf("ft_printf: %d vs %d :printf #8\n",ft_printf("|%+3d|\t", n),		printf("|%+3d|\t", n));
	printf("ft_printf: %d vs %d :printf #9\n",ft_printf("|% d|\t", n),		printf("|% d|\t", n));
	printf("ft_printf: %d vs %d :printf #10\n",ft_printf("|% 1d|\t", n),	printf("|% 1d|\t", n));
	printf("ft_printf: %d vs %d :printf #11\n",ft_printf("|% 2d|\t", n),	printf("|% 2d|\t", n));
	printf("ft_printf: %d vs %d :printf #12\n",ft_printf("|% 3d|\t", n),	printf("|% 3d|\t", n));
	printf("ft_printf: %d vs %d :printf #13\n",ft_printf("|%-d|\t", n),		printf("|%-d|\t", n));
	printf("ft_printf: %d vs %d :printf #14\n",ft_printf("|%-1d|\t", n),	printf("|%-1d|\t", n));
	printf("ft_printf: %d vs %d :printf #15\n",ft_printf("|%-2d|\t", n),	printf("|%-2d|\t", n));
	printf("ft_printf: %d vs %d :printf #16\n",ft_printf("|%-3d|\t", n),	printf("|%-3d|\t", n));
	printf("ft_printf: %d vs %d :printf #17\n",ft_printf("|%+-d|\t", n),	printf("|%+-d|\t", n));
	printf("ft_printf: %d vs %d :printf #18\n",ft_printf("|%+-1d|\t", n),	printf("|%+-1d|\t", n));
	printf("ft_printf: %d vs %d :printf #19\n",ft_printf("|%+-2d|\t", n),	printf("|%+-2d|\t", n));
	printf("ft_printf: %d vs %d :printf #20\n",ft_printf("|%+-3d|\t", n),	printf("|%+-3d|\t", n));
	printf("ft_printf: %d vs %d :printf #21\n",ft_printf("|%+0d|\t", n),	printf("|%+0d|\t", n));
	printf("ft_printf: %d vs %d :printf #22\n",ft_printf("|%+01d|\t", n),	printf("|%+01d|\t", n));
	printf("ft_printf: %d vs %d :printf #23\n",ft_printf("|%+02d|\t", n),	printf("|%+02d|\t", n));
	printf("ft_printf: %d vs %d :printf #24\n",ft_printf("|%+03d|\t", n),	printf("|%+03d|\t", n));
	printf("ft_printf: %d vs %d :printf #25\n",ft_printf("|%0d|\t", n),		printf("|%0d|\t", n));
	printf("ft_printf: %d vs %d :printf #26\n",ft_printf("|% 0d|\t", n),	printf("|% 0d|\t", n));
	printf("ft_printf: %d vs %d :printf #27\n",ft_printf("|% 01d|\t", n),	printf("|% 01d|\t", n));
	printf("ft_printf: %d vs %d :printf #28\n",ft_printf("|% 02d|\t", n),	printf("|% 02d|\t", n));//check me
	printf("ft_printf: %d vs %d :printf #29\n",ft_printf("|% 03d|\t", n),	printf("|% 03d|\t", n));
	printf("ft_printf: %d vs %d :printf #30\n",ft_printf("|%+- 0d|\t", n),	printf("|%+- 0d|\t", n));
	printf("ft_printf: %d vs %d :printf #31\n",ft_printf("|%+- 01d|\t", n),	printf("|%+- 01d|\t", n));
	printf("ft_printf: %d vs %d :printf #32\n",ft_printf("|%01d|\t", n),	printf("|%01d|\t", n));
	printf("ft_printf: %d vs %d :printf #33\n",ft_printf("|%02d|\t", n),	printf("|%02d|\t", n));
	printf("ft_printf: %d vs %d :printf #34\n",ft_printf("|%03d|\t", n),	printf("|%03d|\t", n));
	printf("ft_printf: %d vs %d :printf #35\n",ft_printf("|%04d|\t", n),	printf("|%04d|\t", n));
	printf("ft_printf: %d vs %d :printf #36\n",ft_printf("|%.d|\t", n),		printf("|%.d|\t", n));//start precision checking
	printf("ft_printf: %d vs %d :printf #37\n",ft_printf("|%.1d|\t", n),	printf("|%.1d|\t", n));
	printf("ft_printf: %d vs %d :printf #38\n",ft_printf("|%.2d|\t", n),	printf("|%.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #39\n",ft_printf("|%.3d|\t", n),	printf("|%.3d|\t", n));
	printf("ft_printf: %d vs %d :printf #40\n",ft_printf("|%.4d|\t", n),	printf("|%.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #41\n",ft_printf("|%0.d|\t", n),	printf("|%0.d|\t", n));
	printf("ft_printf: %d vs %d :printf #42\n",ft_printf("|%0.1d|\t", n),	printf("|%0.1d|\t", n));
	printf("ft_printf: %d vs %d :printf #43\n",ft_printf("|%0.2d|\t", n),	printf("|%0.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #44\n",ft_printf("|%0.3d|\t", n),	printf("|%0.3d|\t", n));
	printf("ft_printf: %d vs %d :printf #45\n",ft_printf("|%0.4d|\t", n),	printf("|%0.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #46\n",ft_printf("|%1.4d|\t", n),	printf("|%1.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #47\n",ft_printf("|%2.4d|\t", n),	printf("|%2.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #48\n",ft_printf("|%3.4d|\t", n),	printf("|%3.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #49\n",ft_printf("|%4.4d|\t", n),	printf("|%4.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #50\n",ft_printf("|%5.4d|\t", n),	printf("|%5.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #51\n",ft_printf("|%6.4d|\t", n),	printf("|%6.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #52\n",ft_printf("|%7.4d|\t", n),	printf("|%7.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #53\n",ft_printf("|%01.4d|\t", n),	printf("|%01.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #54\n",ft_printf("|%02.4d|\t", n),	printf("|%02.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #55\n",ft_printf("|%03.4d|\t", n),	printf("|%03.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #56\n",ft_printf("|%04.4d|\t", n),	printf("|%04.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #57\n",ft_printf("|%05.4d|\t", n),	printf("|%05.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #58\n",ft_printf("|%06.4d|\t", n),	printf("|%06.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #59\n",ft_printf("|%05.d|\t", n),	printf("|%05.d|\t", n));
	printf("ft_printf: %d vs %d :printf #60\n",ft_printf("|%1.d|\t", n),	printf("|%1.d|\t", n));
	printf("ft_printf: %d vs %d :printf #61\n",ft_printf("|%2.d|\t", n),	printf("|%2.d|\t", n));
	printf("ft_printf: %d vs %d :printf #62\n",ft_printf("|%3.d|\t", n),	printf("|%3.d|\t", n));
	printf("ft_printf: %d vs %d :printf #63\n",ft_printf("|%4.d|\t", n),	printf("|%4.d|\t", n));
	printf("ft_printf: %d vs %d :printf #64\n",ft_printf("|%5.d|\t", n),	printf("|%5.d|\t", n));
	printf("ft_printf: %d vs %d :printf #66\n",ft_printf("|%+.d|\t", n),	printf("|%+.d|\t", n));
	printf("ft_printf: %d vs %d :printf #67\n",ft_printf("|%+1.2d|\t", n),	printf("|%+1.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #68\n",ft_printf("|%+2.2d|\t", n),	printf("|%+2.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #69\n",ft_printf("|%+3.2d|\t", n),	printf("|%+3.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #70\n",ft_printf("|%+4.2d|\t", n),	printf("|%+4.2d|\t", n));
	printf("ft_printf: %d vs %d :printf #71\n",ft_printf("|%+01.d|\t", n),	printf("|%+01.d|\t", n));
	printf("ft_printf: %d vs %d :printf #72\n",ft_printf("|%+02.d|\t", n),	printf("|%+02.d|\t", n));
	printf("ft_printf: %d vs %d :printf #73\n",ft_printf("|%+03.d|\t", n),	printf("|%+03.d|\t", n));
	printf("ft_printf: %d vs %d :printf #74\n",ft_printf("|%+04.d|\t", n),	printf("|%+04.d|\t", n));
	printf("ft_printf: %d vs %d :printf #75\n",ft_printf("|%+04.4d|\t", n),	printf("|%+04.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #76\n",ft_printf("|%+05.4d|\t", n),	printf("|%+05.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #77\n",ft_printf("|%+06.4d|\t", n),	printf("|%+06.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #78\n",ft_printf("|%+07.4d|\t", n),	printf("|%+07.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #79\n",ft_printf("|%+01.4d|\t", n),	printf("|%+01.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #80\n",ft_printf("|%+02.4d|\t", n),	printf("|%+02.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #81\n",ft_printf("|%+03.4d|\t", n),	printf("|%+03.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #82\n",ft_printf("|%+04.4d|\t", n),	printf("|%+04.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #83\n",ft_printf("|%+-1.4d|\t", n),	printf("|%+-1.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #84\n",ft_printf("|%+-2.4d|\t", n),	printf("|%+-2.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #85\n",ft_printf("|%+-3.4d|\t", n),	printf("|%+-3.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #86\n",ft_printf("|%+-4.4d|\t", n),	printf("|%+-4.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #87\n",ft_printf("|%+-5.4d|\t", n),	printf("|%+-5.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #88\n",ft_printf("|%+-6.4d|\t", n),	printf("|%+-6.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #89\n",ft_printf("|%+-01.4d|\t", n),	printf("|%+-01.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #90\n",ft_printf("|%+-02.4d|\t", n),	printf("|%+-02.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #91\n",ft_printf("|%+-03.4d|\t", n),	printf("|%+-03.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #92\n",ft_printf("|%+-04.4d|\t", n),	printf("|%+-04.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #93\n",ft_printf("|%+-05.4d|\t", n),	printf("|%+-05.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #94\n",ft_printf("|%+-06.4d|\t", n),	printf("|%+-06.4d|\t", n));
	printf("ft_printf: %d vs %d :printf #95\n",ft_printf("|%+-.d|\t", n),	printf("|%+-.d|\t", n));
	printf("ft_printf: %d vs %d :printf #96\n",ft_printf("|%+-1.d|\t", n),	printf("|%+-1.d|\t", n));
	printf("ft_printf: %d vs %d :printf #97\n",ft_printf("|%+-2.d|\t", n),	printf("|%+-2.d|\t", n));
	printf("ft_printf: %d vs %d :printf #98\n",ft_printf("|%+-3.d|\t", n),	printf("|%+-3.d|\t", n));
	printf("ft_printf: %d vs %d :printf #99\n",ft_printf("|%+-4.d|\t", n),	printf("|%+-4.d|\t", n));*/
/*	printf("-------------------------------------SIZE_RELATED---------------------------------\n");
	printf("For char (size z): %zd\n", 128);
	size_t t= UINT_MAX;
	printf("ft_printf: %d vs %d :printf #1\n",ft_printf("|%Ld|\t", t),		printf("|%Ld|\t", t));*/
	printf("------------------------------------ARG_RELATED-----------------------------------\n");
	printf("ft_prinf: %d vs %d :printf #1\n", ft_printf("%3$d, %2$d, %1$d \t", 1, 2, 3), printf("%3$d, %2$d, %1$d \t", 1, 2, 3));
	printf("ft_prinf: %d vs %d :printf #1\n", ft_printf("%2$d, %3$d, %1$d \t", 1, 2, 3), printf("%2$d, %3$d, %1$d \t", 1, 2, 3));
	printf("ft_prinf: %d vs %d :printf #1\n", ft_printf("%1$d, %3$d, %2$d \t", 1, 2, 3), printf("%1$d, %3$d, %2$d \t", 1, 2, 3));
	printf("ft_prinf: %d vs %d :printf #1\n", ft_printf("%3$d, %2$d, %2$d \t", 1, 2, 3), printf("%3$d, %2$d, %2$d \t", 1, 2, 3));
//	printf("ft_prinf: %d vs %d :printf #1\n", ft_printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"));
	
	return (0);
}
