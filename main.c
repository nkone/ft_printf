/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:41:48 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/02 20:47:37 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

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

void	ft_putchar(char c) { write(1, &c, 1); }
// To Do List:
// Learn Dispatch Table to improve coding skills and structure handling.
// Study Exam Questions✓;
// Create struct to collect flags; 
typedef void (*jumper) ();
void	put_a(void) {ft_putchar('a');}
void	put_hello(void) {ft_putstr("hello");}


jumper put_table[2] = {put_a, put_hello};


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
#define	_VALID_TYPES "cpsdiouxXf"

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

int	collect_type(t_print *p)
{
	if (p->type)
		return (0);
	if (*p->str == 'c')
		return (p->type |= _T_C);
	if (*p->str == 's')
		return (p->type |= _T_S);
	if (*p->str == 'p')
		return (p->type |= _T_P);
	if (*p->str == 'd')
		return (p->type |= _T_D);
	if (*p->str == 'i')
		return (p->type |= _T_I);
	if (*p->str == 'o')
		return (p->type |= _T_O);
	if (*p->str == 'u')
		return (p->type |= _T_U);
	if (*p->str == 'x')
		return (p->type |= _T_LX);
	if (*p->str == 'X')
		return (p->type |= _T_UX);
	if (*p->str == 'f')
		return (p->type |= _T_F);
	return (0);
}

int	collector_driver(t_print *p)
{
	while (collect_flag(p))
		p->str++;
	while (collect_type(p))
		p->str++;
//	printf("type: %d\n", p->type);
	if (!p->type)
		return (0);
	return (1);
}
void	_init_print(t_print *p)
{
	p->flag = 0;
	p->pcn = 0;
	p->size = 0;
	p->type = 0;
	p->width = 0;
	p->done = 0;
	p->str = NULL;
}

void	_reset_collector(t_print *p)
{
	p->flag = 0;
	p->pcn = 0;
	p->size = 0;
	p->type = 0;
	p->width = 0;
}
int	print_char(t_print *p)
{
	int		c;

	c = va_arg(p->ap, int);
	ft_putchar(c);
	p->done++;
	return (1);
}


typedef int		jump_table(t_print *p);
jump_table *print_table[] = {
	print_char
};


int	_ft_printf(const char *str, va_list ap)
{
	t_print p;

	_init_print(&p);
	va_copy(p.ap, ap);
	//va_start(p.ap, str);
	p.str = str;
	while (*p.str)
	{
		if (*p.str == '%')
		{
			p.str++;
			if (!collector_driver(&p))
				break;
			//printf("type: %d\n", p.type);
			if (print_table[p.type -1](&p))
				continue;
		}
		else
		{
			ft_putchar(*p.str++);
			p.done++;
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
	done = _ft_printf(str, ap);
	va_end(ap);
	return (done);
}
int main(void){
	char c = 'a';
	printf("%d\n", ft_printf("hi low hello |%c|\n", c));
	printf("%d\n", printf("hi low hello |%c|\n", c));
}
