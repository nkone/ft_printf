/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:41:48 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/08 19:47:44 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"
#include <stddef.h>
#include <limits.h>
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
// Collect size;

#define _F_MINUS	(1U << 0U)
#define _F_PLUS		(1U << 1U)
#define _F_SPACE	(1U << 2U)
#define _F_ZERO		(1U << 3U)
#define _F_HASH		(1U << 4U)

#define _S_H		(1U << 0U)
#define	_S_HH		(1U << 1U)
#define	_S_L		(1U << 2U)
#define _S_LL		(1U << 3U)
#define _S_LF		(1U << 4U)
// For dispatch table use -1 to get correct index
#define _T_MOD		(11)
#define _T_C		(1)
#define _T_S		(2)
#define _T_P		(3)
#define _T_D		(4)
#define _T_I		(5)
#define _T_O		(6)
#define _T_U		(7)
#define _T_LX		(8)
#define _T_UX		(9)
#define _T_F		(10)

#define	_VALID_FLAGS	"-+ 0#"
#define	_VALID_SIZE "hlfFL"
#define	_VALID_TYPES "cs%pdiouxXf"

typedef struct s_print
{
	unsigned int	flag;
	unsigned int	pcn;
	unsigned int	size;
	unsigned int	type;
	unsigned int	width; // ft_atoi();
	unsigned int	done;
	const char		*str;
	va_list			ap;
}			t_print;

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
		return (p->width = va_arg(p->ap, int));
	return (0);
}

int	collect_pcn(t_print *p)
{
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
	if (p->type)
		return (0);
	if (!(ref = ft_strchr(_VALID_TYPES, *p->str)))
		return (0);
	else 
		return (p->type = (ptrdiff_t)(ref - _VALID_TYPES) + 1);
	return (0);
}	
	
int	collector_driver(t_print *p)
{
	while (collect_flag(p))
		p->str++;
//	printf("\nAfter collect flag: %c\n", *p->str);
	(collect_width(p)) && p->str++;
	(collect_pcn(p)) && p->str++;
	(collect_size(p)) && p->str++;
	(collect_type(p)) && p->str++;
	printf("\nflag: %d width: %d pcn: %d size: %d type: %d \n", p->flag, p->width, p->pcn, p->size, p->type);
	if (!p->type)
		return (0);
	return (1);
}

void	init_print(t_print *p)
{
	p->flag = 0;
	p->pcn = 0;
	p->size = 0;
	p->type = 0;
	p->width = 0;
	p->done = 0;
	p->str = NULL;
}

void	reset_collector(t_print *p)
{
	p->flag = 0;
	p->pcn = 0;
	p->size = 0;
	p->type = 0;
	p->width = 0;
}

void	print_char_(void print(char), char c, int space, int flag)
{
	if (flag)
	{
		print(c);
		while (--space)
			ft_putchar(' ');
	}
	else
	{
		while (--space)
			ft_putchar(' ');
		print(c);
	}
}

void	print_char(t_print *p)
{
	char		c;

	c = va_arg(p->ap, int);
	p->done += (p->width) ? (p->width) : 1;
	printf("done: %u\n", p->done);
	if ((p->done) >= INT_MAX)
		return;
	if (p->flag & _F_MINUS)
		print_char_(ft_putchar, c, p->width, 1);
	else if (p->width)
		print_char_(ft_putchar, c, p->width, 0);
	else
		ft_putchar(c);
}

void	print_str_(void	print(const char *), char *s, int space, int flag)
{
	if (flag)
	{
		if (!s)
			print("(null)");
		else
			print(s);
		while (space--)
			ft_putchar(' ');
	}
	else
	{
		while (space--)
			ft_putchar(' ');
		if (!s)
			print("(null)");
		else
			print(s);
	}
}

void	print_str(t_print *p)
{
	unsigned int	space;
	unsigned int len;
	char	*s;

	s = va_arg(p->ap, char *);
	len = (s) ? ft_strlen(s) : 6;
	space = (len > p->width) ? 0 : (p->width - len);
	p->done += (space) ? (space + len) : len;
	printf("done string: %u\n", p->done);
	if ((p->done) >= INT_MAX)
		return;
	if (p->flag & _F_MINUS)
		print_str_(ft_putstr, s, space, 1);
	else if (space)
		print_str_(ft_putstr, s, space, 0);
	else if (!s)
		ft_putstr("(null)");
	else
		ft_putstr(s);
}

void	print_mod(t_print *p)
{
	p->done += (p->width) ? (p->width) : 1;
	if (p->flag & _F_MINUS)
		print_char_(ft_putchar, '%', p->width, 1);
	else if (p->width)
		print_char_(ft_putchar, '%', p->width, 0);
	else
		ft_putchar('%');
}

typedef void		jump_table(t_print *p);
jump_table *print_table[] = {
	print_char,
	print_str,
	print_mod
};

int	ft_printf_(const char *str, va_list ap)
{
	t_print p;

	init_print(&p);
	va_copy(p.ap, ap);
	//va_start(p.ap, str);
	p.str = str;
	while (*p.str)
	{
		reset_collector(&p);
		if (*p.str == '%')
		{
			p.str++;
			if (!collector_driver(&p))
				break;
			 print_table[p.type -1](&p);
			 printf("pdone: %u\n", p.done);
			 if (p.done > INT_MAX)
				 return (-1);
		}
		else
		{
			p.done++;
			if (p.done > INT_MAX)
				return (-1);
			ft_putchar(*p.str++);
		}
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


int main(void){
	char *s = NULL;
	char c = 'a';
	printf("p return %d\n", ft_printf("%2147483646s\n",s));
	printf("p return %d\n", printf("%2147483647s\n",s));
}
