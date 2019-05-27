/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:41:48 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/26 16:56:24 by phtruong         ###   ########.fr       */
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


void	print_mod(t_print *p)
{
	p->done += (p->width) ? (p->width) : 1;
	print_char_(p, '%');
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

void	print_unbr(t_print *p)
{
	uintmax_t n;
	int len;
	int space;
	int pads;
	
	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_nbr_len(n);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_space(p, n, pads, len);
	p->done += (space + pads + len);
	if (p->done >= INT_MAX)
		return ;
	if (n >= 0 && (p->flag & _F_PLUS || p->flag & _F_SPACE))
		p->done++;
	print_unbr_driver(p, n, space, pads);
}

int	get_unbr_len_base(uintmax_t n, int base)
{
	int len;

	if (base < 2 || base > 16)
		return (0);
	if (!n)
		return (1);
	len = 1;
	while (n/=base)
		len++;
	return (len);
}

void	print_binary(uintmax_t n)
{
	if (n >= 2)
	{
		print_binary(n/2);
		(n & 1) ? ft_putchar('1') : ft_putchar('0');
	}
	else
		(n & 1) ? ft_putchar('1') : ft_putchar('0');
}

void	print_binary_case1(uintmax_t n)
{
	print_binary(n);
}

void	print_binary_case2(t_print *p, uintmax_t n, int space)
{
	char c;

	c = ' ';
	if (p->flag & _F_PCN || p->flag & _F_MINUS)
		c = ' ';
	else if (p->flag & _F_ZERO)
		c = '0';
	(!(p->flag & _F_MINUS)) && put_nchar(c, space);
	print_binary(n);
	(p->flag & _F_MINUS) && put_nchar(c, space);
}

void	print_binary_case3(uintmax_t n, int pads)
{
	put_nchar('0', pads);
	print_binary(n);
}

void	print_binary_case4(t_print *p, uintmax_t n, int space, int pads)
{
	(!(p->flag & _F_MINUS)) && put_nchar(' ', space);
	put_nchar('0', pads);
	print_binary(n);
	(p->flag & _F_MINUS) && put_nchar(' ', space);
}

void	print_binary_driver(t_print *p, uintmax_t n, int space, int pads)
{
	if (!space && !pads)
		print_binary_case1(n);
	else if (space && !pads)
		print_binary_case2(p, n, space);
	else if (!space && pads)
		print_binary_case3(n, pads);
	else if (space && pads)
		print_binary_case4(p, n, space, pads);
}

void	print_unbr_base2(t_print *p)
{
	uintmax_t n;
	int len;
	int space;
	int pads;

	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_unbr_len_base(n, 2);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_space(p, n, pads, len);
	p->done += (space + pads + len);
	if (p->done >= INT_MAX)
		return ;
	print_binary_driver(p, n, space, pads);
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
{
//	printf("-------------------------------------STRINGS---------------------------------------\n");
//	char *s = "hi low";
//	printf("ft_printf: %d vs %d :printf #1\n",ft_printf("|%s|\t", s),		printf("|%s|\t", s));
//	printf("ft_printf: %d vs %d :printf #2\n",ft_printf("|%1s|\t", s),		printf("|%1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #3\n",ft_printf("|%2s|\t", s),		printf("|%2s|\t", s));
//	printf("ft_printf: %d vs %d :printf #4\n",ft_printf("|%3s|\t", s),		printf("|%3s|\t", s));
//	printf("ft_printf: %d vs %d :printf #5\n",ft_printf("|%4s|\t", s),		printf("|%4s|\t", s));
//	printf("ft_printf: %d vs %d :printf #6\n",ft_printf("|%5s|\t", s),		printf("|%5s|\t", s));
//	printf("ft_printf: %d vs %d :printf #7\n",ft_printf("|%6s|\t", s),		printf("|%6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #8\n",ft_printf("|%7s|\t", s),		printf("|%7s|\t", s));
//	printf("ft_printf: %d vs %d :printf #9\n",ft_printf("|%8s|\t", s),		printf("|%8s|\t", s));
//	printf("ft_printf: %d vs %d :printf #10\n",ft_printf("|%9s|\t", s),		printf("|%9s|\t", s));
//	//undefined behavior
//	printf("ft_printf: %d vs %d :printf #11\n",ft_printf("|%+1s|\t", s),		printf("|%+1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #12\n",ft_printf("|%+2s|\t", s),		printf("|%+2s|\t", s));
//	printf("ft_printf: %d vs %d :printf #13\n",ft_printf("|%+3s|\t", s),		printf("|%+3s|\t", s));
//	printf("ft_printf: %d vs %d :printf #14\n",ft_printf("|%+4s|\t", s),		printf("|%+4s|\t", s));
//	printf("ft_printf: %d vs %d :printf #15\n",ft_printf("|%+5s|\t", s),		printf("|%+5s|\t", s));
//	printf("ft_printf: %d vs %d :printf #16\n",ft_printf("|%+6s|\t", s),		printf("|%+6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #17\n",ft_printf("|%+7s|\t", s),		printf("|%+7s|\t", s));
//	printf("ft_printf: %d vs %d :printf #18\n",ft_printf("|%+8s|\t", s),		printf("|%+8s|\t", s));
//	printf("ft_printf: %d vs %d :printf #19\n",ft_printf("|%+9s|\t", s),		printf("|%+9s|\t", s));
//	printf("ft_printf: %d vs %d :printf #20\n",ft_printf("|%+01s|\t", s),		printf("|%+01s|\t", s));
//	printf("ft_printf: %d vs %d :printf #21\n",ft_printf("|%+02s|\t", s),		printf("|%+02s|\t", s));
//	printf("ft_printf: %d vs %d :printf #22\n",ft_printf("|%+03s|\t", s),		printf("|%+03s|\t", s));
//	printf("ft_printf: %d vs %d :printf #23\n",ft_printf("|%+04s|\t", s),		printf("|%+04s|\t", s));
//	printf("ft_printf: %d vs %d :printf #24\n",ft_printf("|%+05s|\t", s),		printf("|%+05s|\t", s));
//	printf("ft_printf: %d vs %d :printf #25\n",ft_printf("|%+06s|\t", s),		printf("|%+06s|\t", s));
//	printf("ft_printf: %d vs %d :printf #26\n",ft_printf("|%+07s|\t", s),		printf("|%+07s|\t", s));
//	printf("ft_printf: %d vs %d :printf #27\n",ft_printf("|%+08s|\t", s),		printf("|%+08s|\t", s));
//	printf("ft_printf: %d vs %d :printf #28\n",ft_printf("|%+09s|\t", s),		printf("|%+09s|\t", s));
//	//0 decoy
//	printf("ft_printf: %d vs %d :printf #29\n",ft_printf("|%00s|\t", s),		printf("|%00s|\t", s));
//	printf("ft_printf: %d vs %d :printf #30\n",ft_printf("|%010s|\t", s),		printf("|%010s|\t", s));
//	printf("ft_printf: %d vs %d :printf #31\n",ft_printf("|%001s|\t", s),		printf("|%001s|\t", s));
//	printf("ft_printf: %d vs %d :printf #32\n",ft_printf("|%020s|\t", s),		printf("|%020s|\t", s));
//	printf("ft_printf: %d vs %d :printf #33\n",ft_printf("|%000s|\t", s),		printf("|%000s|\t", s));
//	printf("ft_printf: %d vs %d :printf #34\n",ft_printf("|%0000s|\t", s),		printf("|%0000s|\t", s));
//	printf("ft_printf: %d vs %d :printf #35\n",ft_printf("|%-00s|\t", s),		printf("|%-00s|\t", s));
//	printf("ft_printf: %d vs %d :printf #36\n",ft_printf("|%0-0s|\t", s),		printf("|%0-0s|\t", s));
//	printf("ft_printf: %d vs %d :printf #37\n",ft_printf("|%00-s|\t", s),		printf("|%00-s|\t", s));
//	// Precision no width
//	printf("ft_printf: %d vs %d :printf #38\n",ft_printf("|%.s|\t", s),		printf("|%.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #39\n",ft_printf("|%.0s|\t", s),		printf("|%.0s|\t", s));
//	printf("ft_printf: %d vs %d :printf #40\n",ft_printf("|%.1s|\t", s),		printf("|%.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #41\n",ft_printf("|%.2s|\t", s),		printf("|%.2s|\t", s));
//	printf("ft_printf: %d vs %d :printf #42\n",ft_printf("|%.3s|\t", s),		printf("|%.3s|\t", s));
//	printf("ft_printf: %d vs %d :printf #43\n",ft_printf("|%.4s|\t", s),		printf("|%.4s|\t", s));
//	printf("ft_printf: %d vs %d :printf #44\n",ft_printf("|%.5s|\t", s),		printf("|%.5s|\t", s));
//	printf("ft_printf: %d vs %d :printf #45\n",ft_printf("|%.6s|\t", s),		printf("|%.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #46\n",ft_printf("|%.7s|\t", s),		printf("|%.7s|\t", s));
//	printf("ft_printf: %d vs %d :printf #47\n",ft_printf("|%.8s|\t", s),		printf("|%.8s|\t", s));
//	printf("ft_printf: %d vs %d :printf #48\n",ft_printf("|%.9s|\t", s),		printf("|%.9s|\t", s));
//	printf("ft_printf: %d vs %d :printf #49\n",ft_printf("|%.00s|\t", s),		printf("|%.00s|\t", s));
//	printf("ft_printf: %d vs %d :printf #50\n",ft_printf("|%.01s|\t", s),		printf("|%.01s|\t", s));
//	printf("ft_printf: %d vs %d :printf #51\n",ft_printf("|%.02s|\t", s),		printf("|%.02s|\t", s));
//	printf("ft_printf: %d vs %d :printf #52\n",ft_printf("|%.03s|\t", s),		printf("|%.03s|\t", s));
//	printf("ft_printf: %d vs %d :printf #53\n",ft_printf("|%.04s|\t", s),		printf("|%.04s|\t", s));
//	printf("ft_printf: %d vs %d :printf #54\n",ft_printf("|%.05s|\t", s),		printf("|%.05s|\t", s));
//	printf("ft_printf: %d vs %d :printf #55\n",ft_printf("|%.06s|\t", s),		printf("|%.06s|\t", s));
//	printf("ft_printf: %d vs %d :printf #56\n",ft_printf("|%.07s|\t", s),		printf("|%.07s|\t", s));
//	printf("ft_printf: %d vs %d :printf #57\n",ft_printf("|%.08s|\t", s),		printf("|%.08s|\t", s));
//	printf("ft_printf: %d vs %d :printf #58\n",ft_printf("|%.09s|\t", s),		printf("|%.09s|\t", s));
//	//Decoy minus flag
//	printf("ft_printf: %d vs %d :printf #59\n",ft_printf("|%-.s|\t", s),		printf("|%-.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #60\n",ft_printf("|%-.0s|\t", s),		printf("|%-.0s|\t", s));
//	printf("ft_printf: %d vs %d :printf #61\n",ft_printf("|%-.1s|\t", s),		printf("|%-.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #62\n",ft_printf("|%-.2s|\t", s),		printf("|%-.2s|\t", s));
//	printf("ft_printf: %d vs %d :printf #63\n",ft_printf("|%-.3s|\t", s),		printf("|%-.3s|\t", s));
//	printf("ft_printf: %d vs %d :printf #64\n",ft_printf("|%-.4s|\t", s),		printf("|%-.4s|\t", s));
//	printf("ft_printf: %d vs %d :printf #65\n",ft_printf("|%-.5s|\t", s),		printf("|%-.5s|\t", s));
//	printf("ft_printf: %d vs %d :printf #66\n",ft_printf("|%-.6s|\t", s),		printf("|%-.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #67\n",ft_printf("|%-.7s|\t", s),		printf("|%-.7s|\t", s));
//	printf("ft_printf: %d vs %d :printf #68\n",ft_printf("|%-.8s|\t", s),		printf("|%-.8s|\t", s));
//	printf("ft_printf: %d vs %d :printf #69\n",ft_printf("|%-.9s|\t", s),		printf("|%-.9s|\t", s));
//	printf("ft_printf: %d vs %d :printf #70\n",ft_printf("|%-.00s|\t", s),		printf("|%-.00s|\t", s));
//	printf("ft_printf: %d vs %d :printf #71\n",ft_printf("|%-.01s|\t", s),		printf("|%-.01s|\t", s));
//	printf("ft_printf: %d vs %d :printf #72\n",ft_printf("|%-.02s|\t", s),		printf("|%-.02s|\t", s));
//	printf("ft_printf: %d vs %d :printf #73\n",ft_printf("|%-.03s|\t", s),		printf("|%-.03s|\t", s));
//	printf("ft_printf: %d vs %d :printf #74\n",ft_printf("|%-.04s|\t", s),		printf("|%-.04s|\t", s));
//	printf("ft_printf: %d vs %d :printf #75\n",ft_printf("|%-.05s|\t", s),		printf("|%-.05s|\t", s));
//	printf("ft_printf: %d vs %d :printf #76\n",ft_printf("|%-.06s|\t", s),		printf("|%-.06s|\t", s));
//	printf("ft_printf: %d vs %d :printf #77\n",ft_printf("|%-.07s|\t", s),		printf("|%-.07s|\t", s));
//	printf("ft_printf: %d vs %d :printf #78\n",ft_printf("|%-.08s|\t", s),		printf("|%-.08s|\t", s));
//	printf("ft_printf: %d vs %d :printf #79\n",ft_printf("|%-.09s|\t", s),		printf("|%-.09s|\t", s));
//	//Decoy space flag
//	printf("ft_printf: %d vs %d :printf #80\n",ft_printf("|% .s|\t", s),		printf("|% .s|\t", s));
//	printf("ft_printf: %d vs %d :printf #81\n",ft_printf("|% .0s|\t", s),		printf("|% .0s|\t", s));
//	printf("ft_printf: %d vs %d :printf #82\n",ft_printf("|% .1s|\t", s),		printf("|% .1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #83\n",ft_printf("|% .2s|\t", s),		printf("|% .2s|\t", s));
//	printf("ft_printf: %d vs %d :printf #84\n",ft_printf("|% .3s|\t", s),		printf("|% .3s|\t", s));
//	printf("ft_printf: %d vs %d :printf #85\n",ft_printf("|% .4s|\t", s),		printf("|% .4s|\t", s));
//	printf("ft_printf: %d vs %d :printf #86\n",ft_printf("|% .5s|\t", s),		printf("|% .5s|\t", s));
//	printf("ft_printf: %d vs %d :printf #87\n",ft_printf("|% .6s|\t", s),		printf("|% .6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #88\n",ft_printf("|% .7s|\t", s),		printf("|% .7s|\t", s));
//	printf("ft_printf: %d vs %d :printf #89\n",ft_printf("|% .8s|\t", s),		printf("|% .8s|\t", s));
//	printf("ft_printf: %d vs %d :printf #90\n",ft_printf("|% .9s|\t", s),		printf("|% .9s|\t", s));
//	printf("ft_printf: %d vs %d :printf #91\n",ft_printf("|% .00s|\t", s),		printf("|% .00s|\t", s));
//	printf("ft_printf: %d vs %d :printf #92\n",ft_printf("|% .01s|\t", s),		printf("|% .01s|\t", s));
//	printf("ft_printf: %d vs %d :printf #93\n",ft_printf("|% .02s|\t", s),		printf("|% .02s|\t", s));
//	printf("ft_printf: %d vs %d :printf #94\n",ft_printf("|% .03s|\t", s),		printf("|% .03s|\t", s));
//	printf("ft_printf: %d vs %d :printf #95\n",ft_printf("|% .04s|\t", s),		printf("|% .04s|\t", s));
//	printf("ft_printf: %d vs %d :printf #96\n",ft_printf("|% .05s|\t", s),		printf("|% .05s|\t", s));
//	printf("ft_printf: %d vs %d :printf #97\n",ft_printf("|% .06s|\t", s),		printf("|% .06s|\t", s));
//	printf("ft_printf: %d vs %d :printf #98\n",ft_printf("|% .07s|\t", s),		printf("|% .07s|\t", s));
//	printf("ft_printf: %d vs %d :printf #99\n",ft_printf("|% .08s|\t", s),		printf("|% .08s|\t", s));
//	printf("ft_printf: %d vs %d :printf #100\n",ft_printf("|% .09s|\t", s),		printf("|% .09s|\t", s));
//	//no precision with width
//	printf("ft_printf: %d vs %d :printf #101\n",ft_printf("|%0.s|\t", s),		printf("|%0.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #102\n",ft_printf("|%1.s|\t", s),		printf("|%1.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #103\n",ft_printf("|%2.s|\t", s),		printf("|%2.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #104\n",ft_printf("|%3.s|\t", s),		printf("|%3.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #105\n",ft_printf("|%4.s|\t", s),		printf("|%4.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #106\n",ft_printf("|%5.s|\t", s),		printf("|%5.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #107\n",ft_printf("|%6.s|\t", s),		printf("|%6.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #108\n",ft_printf("|%7.s|\t", s),		printf("|%7.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #109\n",ft_printf("|%8.s|\t", s),		printf("|%8.s|\t", s));
//	printf("ft_printf: %d vs %d :printf #110\n",ft_printf("|%9.s|\t", s),		printf("|%9.s|\t", s));
//	//low precision with width
//	printf("ft_printf: %d vs %d :printf #111\n",ft_printf("|%0.1s|\t", s),		printf("|%0.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #112\n",ft_printf("|%1.1s|\t", s),		printf("|%1.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #113\n",ft_printf("|%2.1s|\t", s),		printf("|%2.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #114\n",ft_printf("|%3.1s|\t", s),		printf("|%3.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #115\n",ft_printf("|%4.1s|\t", s),		printf("|%4.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #116\n",ft_printf("|%5.1s|\t", s),		printf("|%5.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #117\n",ft_printf("|%6.1s|\t", s),		printf("|%6.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #118\n",ft_printf("|%7.1s|\t", s),		printf("|%7.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #119\n",ft_printf("|%8.1s|\t", s),		printf("|%8.1s|\t", s));
//	printf("ft_printf: %d vs %d :printf #120\n",ft_printf("|%0.1s|\t", s),		printf("|%0.1s|\t", s));
//	//perfect precision with width
//	printf("ft_printf: %d vs %d :printf #121\n",ft_printf("|%0.6s|\t", s),		printf("|%0.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #122\n",ft_printf("|%1.6s|\t", s),		printf("|%1.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #123\n",ft_printf("|%2.6s|\t", s),		printf("|%2.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #124\n",ft_printf("|%3.6s|\t", s),		printf("|%3.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #125\n",ft_printf("|%4.6s|\t", s),		printf("|%4.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #126\n",ft_printf("|%5.6s|\t", s),		printf("|%5.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #127\n",ft_printf("|%6.6s|\t", s),		printf("|%6.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #128\n",ft_printf("|%7.6s|\t", s),		printf("|%7.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #129\n",ft_printf("|%8.6s|\t", s),		printf("|%8.6s|\t", s));
//	//Wombo combo perfect precision_width
//	printf("ft_printf: %d vs %d :printf #130\n",ft_printf("|%+- 06.6s|\t", s),		printf("|%+- 06.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #131\n",ft_printf("|%-+ 06.6s|\t", s),		printf("|%-+ 06.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #132\n",ft_printf("|%+ -06.6s|\t", s),		printf("|%+ -06.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #133\n",ft_printf("|%+0 -6.6s|\t", s),		printf("|%+0 -6.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #134\n",ft_printf("|% +-06.6s|\t", s),		printf("|% +-06.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #135\n",ft_printf("|%0+- 6.6s|\t", s),		printf("|%0+- 6.6s|\t", s));
//	//Wombo combo width > precision
//	printf("ft_printf: %d vs %d :printf #136\n",ft_printf("|%+- 07.6s|\t", s),		printf("|%+- 07.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #137\n",ft_printf("|%-+ 08.6s|\t", s),		printf("|%-+ 08.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #138\n",ft_printf("|% +-09.6s|\t", s),		printf("|% +-09.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #139\n",ft_printf("|%0-+ 10.6s|\t", s),		printf("|%0-+ 10.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #140\n",ft_printf("|%+0- 11.6s|\t", s),		printf("|%+0- 11.6s|\t", s));
//	printf("ft_printf: %d vs %d :printf #141\n",ft_printf("|%-0+ 12.6s|\t", s),		printf("|%-0+ 12.6s|\t", s));

//	int n = 0;
//	printf("-------------------------------------D_BASICS---------------------------------------\n");
//	printf("For int n: %d\n", n);
//	printf("ft_printf: %d vs %d :printf #1\n",ft_printf("|%d|\t", n),		printf("|%d|\t", n));
//	printf("ft_printf: %d vs %d :printf #2\n",ft_printf("|%1d|\t", n),		printf("|%1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #3\n",ft_printf("|%2d|\t", n),		printf("|%2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #4\n",ft_printf("|%3d|\t", n),		printf("|%3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #5\n",ft_printf("|%+d|\t", n),		printf("|%+d|\t", n));
//	printf("ft_printf: %d vs %d :printf #6\n",ft_printf("|%+1d|\t", n),		printf("|%+1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #7\n",ft_printf("|%+2d|\t", n),		printf("|%+2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #8\n",ft_printf("|%+3d|\t", n),		printf("|%+3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #9\n",ft_printf("|% d|\t", n),		printf("|% d|\t", n));
//	printf("ft_printf: %d vs %d :printf #10\n",ft_printf("|% 1d|\t", n),	printf("|% 1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #11\n",ft_printf("|% 2d|\t", n),	printf("|% 2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #12\n",ft_printf("|% 3d|\t", n),	printf("|% 3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #13\n",ft_printf("|%-d|\t", n),		printf("|%-d|\t", n));
//	printf("ft_printf: %d vs %d :printf #14\n",ft_printf("|%-1d|\t", n),	printf("|%-1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #15\n",ft_printf("|%-2d|\t", n),	printf("|%-2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #16\n",ft_printf("|%-3d|\t", n),	printf("|%-3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #17\n",ft_printf("|%+-d|\t", n),	printf("|%+-d|\t", n));
//	printf("ft_printf: %d vs %d :printf #18\n",ft_printf("|%+-1d|\t", n),	printf("|%+-1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #19\n",ft_printf("|%+-2d|\t", n),	printf("|%+-2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #20\n",ft_printf("|%+-3d|\t", n),	printf("|%+-3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #21\n",ft_printf("|%+0d|\t", n),	printf("|%+0d|\t", n));
//	printf("ft_printf: %d vs %d :printf #22\n",ft_printf("|%+01d|\t", n),	printf("|%+01d|\t", n));
//	printf("ft_printf: %d vs %d :printf #23\n",ft_printf("|%+02d|\t", n),	printf("|%+02d|\t", n));
//	printf("ft_printf: %d vs %d :printf #24\n",ft_printf("|%+03d|\t", n),	printf("|%+03d|\t", n));
//	printf("ft_printf: %d vs %d :printf #25\n",ft_printf("|%0d|\t", n),		printf("|%0d|\t", n));
//	printf("ft_printf: %d vs %d :printf #26\n",ft_printf("|% 0d|\t", n),	printf("|% 0d|\t", n));
//	printf("ft_printf: %d vs %d :printf #27\n",ft_printf("|% 01d|\t", n),	printf("|% 01d|\t", n));
//	printf("ft_printf: %d vs %d :printf #28\n",ft_printf("|% 02d|\t", n),	printf("|% 02d|\t", n));//check me
//	printf("ft_printf: %d vs %d :printf #29\n",ft_printf("|% 03d|\t", n),	printf("|% 03d|\t", n));
//	printf("ft_printf: %d vs %d :printf #30\n",ft_printf("|%+- 0d|\t", n),	printf("|%+- 0d|\t", n));
//	printf("ft_printf: %d vs %d :printf #31\n",ft_printf("|%+- 01d|\t", n),	printf("|%+- 01d|\t", n));
//	printf("ft_printf: %d vs %d :printf #32\n",ft_printf("|%01d|\t", n),	printf("|%01d|\t", n));
//	printf("ft_printf: %d vs %d :printf #33\n",ft_printf("|%02d|\t", n),	printf("|%02d|\t", n));
//	printf("ft_printf: %d vs %d :printf #34\n",ft_printf("|%03d|\t", n),	printf("|%03d|\t", n));
//	printf("ft_printf: %d vs %d :printf #35\n",ft_printf("|%04d|\t", n),	printf("|%04d|\t", n));
//	printf("ft_printf: %d vs %d :printf #36\n",ft_printf("|%.d|\t", n),		printf("|%.d|\t", n));//start precision checking
//	printf("ft_printf: %d vs %d :printf #37\n",ft_printf("|%.1d|\t", n),	printf("|%.1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #38\n",ft_printf("|%.2d|\t", n),	printf("|%.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #39\n",ft_printf("|%.3d|\t", n),	printf("|%.3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #40\n",ft_printf("|%.4d|\t", n),	printf("|%.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #41\n",ft_printf("|%0.d|\t", n),	printf("|%0.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #42\n",ft_printf("|%0.1d|\t", n),	printf("|%0.1d|\t", n));
//	printf("ft_printf: %d vs %d :printf #43\n",ft_printf("|%0.2d|\t", n),	printf("|%0.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #44\n",ft_printf("|%0.3d|\t", n),	printf("|%0.3d|\t", n));
//	printf("ft_printf: %d vs %d :printf #45\n",ft_printf("|%0.4d|\t", n),	printf("|%0.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #46\n",ft_printf("|%1.4d|\t", n),	printf("|%1.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #47\n",ft_printf("|%2.4d|\t", n),	printf("|%2.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #48\n",ft_printf("|%3.4d|\t", n),	printf("|%3.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #49\n",ft_printf("|%4.4d|\t", n),	printf("|%4.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #50\n",ft_printf("|%5.4d|\t", n),	printf("|%5.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #51\n",ft_printf("|%6.4d|\t", n),	printf("|%6.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #52\n",ft_printf("|%7.4d|\t", n),	printf("|%7.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #53\n",ft_printf("|%01.4d|\t", n),	printf("|%01.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #54\n",ft_printf("|%02.4d|\t", n),	printf("|%02.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #55\n",ft_printf("|%03.4d|\t", n),	printf("|%03.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #56\n",ft_printf("|%04.4d|\t", n),	printf("|%04.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #57\n",ft_printf("|%05.4d|\t", n),	printf("|%05.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #58\n",ft_printf("|%06.4d|\t", n),	printf("|%06.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #59\n",ft_printf("|%05.d|\t", n),	printf("|%05.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #60\n",ft_printf("|%1.d|\t", n),	printf("|%1.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #61\n",ft_printf("|%2.d|\t", n),	printf("|%2.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #62\n",ft_printf("|%3.d|\t", n),	printf("|%3.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #63\n",ft_printf("|%4.d|\t", n),	printf("|%4.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #64\n",ft_printf("|%5.d|\t", n),	printf("|%5.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #66\n",ft_printf("|%+.d|\t", n),	printf("|%+.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #67\n",ft_printf("|%+1.2d|\t", n),	printf("|%+1.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #68\n",ft_printf("|%+2.2d|\t", n),	printf("|%+2.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #69\n",ft_printf("|%+3.2d|\t", n),	printf("|%+3.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #70\n",ft_printf("|%+4.2d|\t", n),	printf("|%+4.2d|\t", n));
//	printf("ft_printf: %d vs %d :printf #71\n",ft_printf("|%+01.d|\t", n),	printf("|%+01.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #72\n",ft_printf("|%+02.d|\t", n),	printf("|%+02.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #73\n",ft_printf("|%+03.d|\t", n),	printf("|%+03.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #74\n",ft_printf("|%+04.d|\t", n),	printf("|%+04.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #75\n",ft_printf("|%+04.4d|\t", n),	printf("|%+04.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #76\n",ft_printf("|%+05.4d|\t", n),	printf("|%+05.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #77\n",ft_printf("|%+06.4d|\t", n),	printf("|%+06.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #78\n",ft_printf("|%+07.4d|\t", n),	printf("|%+07.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #79\n",ft_printf("|%+01.4d|\t", n),	printf("|%+01.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #80\n",ft_printf("|%+02.4d|\t", n),	printf("|%+02.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #81\n",ft_printf("|%+03.4d|\t", n),	printf("|%+03.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #82\n",ft_printf("|%+04.4d|\t", n),	printf("|%+04.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #83\n",ft_printf("|%+-1.4d|\t", n),	printf("|%+-1.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #84\n",ft_printf("|%+-2.4d|\t", n),	printf("|%+-2.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #85\n",ft_printf("|%+-3.4d|\t", n),	printf("|%+-3.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #86\n",ft_printf("|%+-4.4d|\t", n),	printf("|%+-4.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #87\n",ft_printf("|%+-5.4d|\t", n),	printf("|%+-5.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #88\n",ft_printf("|%+-6.4d|\t", n),	printf("|%+-6.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #89\n",ft_printf("|%+-01.4d|\t", n),	printf("|%+-01.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #90\n",ft_printf("|%+-02.4d|\t", n),	printf("|%+-02.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #91\n",ft_printf("|%+-03.4d|\t", n),	printf("|%+-03.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #92\n",ft_printf("|%+-04.4d|\t", n),	printf("|%+-04.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #93\n",ft_printf("|%+-05.4d|\t", n),	printf("|%+-05.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #94\n",ft_printf("|%+-06.4d|\t", n),	printf("|%+-06.4d|\t", n));
//	printf("ft_printf: %d vs %d :printf #95\n",ft_printf("|%+-.d|\t", n),	printf("|%+-.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #96\n",ft_printf("|%+-1.d|\t", n),	printf("|%+-1.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #97\n",ft_printf("|%+-2.d|\t", n),	printf("|%+-2.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #98\n",ft_printf("|%+-3.d|\t", n),	printf("|%+-3.d|\t", n));
//	printf("ft_printf: %d vs %d :printf #99\n",ft_printf("|%+-4.d|\t", n),	printf("|%+-4.d|\t", n));

	printf("-------------------------------------UNSIGNED_INT---------------------------------------\n");
	unsigned int u = UINT16_MAX;
	printf("ft_printf: %d vs %d :printf #1\n", ft_printf("|%u|\t", u),	printf("|%u|\t", u));
	printf("ft_printf: %d vs %d :printf #2\n", ft_printf("|%1u|\t", u),	printf("|%1u|\t", u));
	printf("ft_printf: %d vs %d :printf #3\n", ft_printf("|%2u|\t", u),	printf("|%2u|\t", u));
	printf("ft_printf: %d vs %d :printf #4\n", ft_printf("|%3u|\t", u),	printf("|%3u|\t", u));
	printf("ft_printf: %d vs %d :printf #5\n", ft_printf("|%4u|\t", u),	printf("|%4u|\t", u));
	printf("ft_printf: %d vs %d :printf #6\n", ft_printf("|%5u|\t", u),	printf("|%5u|\t", u));
	printf("ft_printf: %d vs %d :printf #7\n", ft_printf("|%20u|\t", u),	printf("|%20u|\t", u));
	printf("ft_printf: %d vs %d :printf #8\n", ft_printf("|%21u|\t", u),	printf("|%21u|\t", u));
	printf("ft_printf: %d vs %d :printf #9\n", ft_printf("|%22u|\t", u),	printf("|%22u|\t", u));
	printf("ft_printf: %d vs %d :printf #10\n", ft_printf("|%23u|\t", u),	printf("|%23u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%24u|\t", u),	printf("|%24u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.u|\t", u),	printf("|%10.u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.1u|\t", u),	printf("|%10.1u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.2u|\t", u),	printf("|%10.2u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.3u|\t", u),	printf("|%10.3u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.4u|\t", u),	printf("|%10.4u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.5u|\t", u),	printf("|%10.5u|\t", u));
	printf("ft_printf: %d vs %d :printf #11\n", ft_printf("|%10.6u|\t", u),	printf("|%10.6u|\t", u));

	printf("-------------------------------------SIZE_RELATED---------------------------------\n");
	printf("For char (size z): %zd\n");
	size_t t= UINT_MAX;
	printf("ft_printf: %d vs %d :printf #1\n",ft_printf("|%Ld|\t", t),		printf("|%Ld|\t", t));

	printf("------------------------------------ARG_BONUS-----------------------------------\n");
	printf("NUMBER RELATED\n");
	printf("ft_printf: %d vs %d :printf #1\n", ft_printf("%3$d, %2$d, %1$d \t", 1, 2, 3), printf("%3$d, %2$d, %1$d \t", 1, 2, 3));
	printf("ft_printf: %d vs %d :printf #2\n", ft_printf("%2$d, %3$d, %1$d \t", 1, 2, 3), printf("%2$d, %3$d, %1$d \t", 1, 2, 3));
	printf("ft_printf: %d vs %d :printf #3\n", ft_printf("%1$d, %3$d, %2$d \t", 1, 2, 3), printf("%1$d, %3$d, %2$d \t", 1, 2, 3));
	printf("ft_printf: %d vs %d :printf #4\n", ft_printf("%3$d, %2$d, %2$d \t", 1, 2, 3), printf("%3$d, %2$d, %2$d \t", 1, 2, 3));
	printf("STRING RELATED\n");
	printf("ft_printf: %d vs %d :printf #1\n", ft_printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #2\n", ft_printf("%2$s, %3$s, %1$s \t", "hi", "low", "hello"), printf("%2$s, %3$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #3\n", ft_printf("%1$s, %2$s, %3$s \t", "hi", "low", "hello"), printf("%1$s, %2$s, %3$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #4\n", ft_printf("%2$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%2$s, %2$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #5\n", ft_printf("%3$s, %2$s, %3$s \t", "hi", "low", "hello"), printf("%3$s, %2$s, %3$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #6\n", ft_printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%3$s, %2$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #7\n", ft_printf("%1$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%1$s, %2$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #8\n", ft_printf("%3$s, %3$s, %3$s \t", "hi", "low", "hello"), printf("%3$s, %3$s, %3$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #9\n", ft_printf("%2$s, %2$s, %1$s \t", "hi", "low", "hello"), printf("%2$s, %2$s, %1$s \t", "hi", "low", "hello"));
	printf("ft_printf: %d vs %d :printf #10\n", ft_printf("%2$s, %2$s, %3$s \t", "hi", "low", "hello"), printf("%2$s, %2$s, %3$s \t", "hi", "low", "hello"));

	printf("------------------------------------STAR_BONUS------------------------------------\n");
	int width = -5;
	printf("ft_printf: %d vs %d :printf #1\n", ft_printf("|%*d| \t", width, 123), printf("|%*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #2\n", ft_printf("|%+*d| \t", width, 123), printf("|%+*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #3\n", ft_printf("|%-*d| \t", width, 123), printf("|%-*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #4\n", ft_printf("|%+-*d| \t", width, 123), printf("|%+-*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #5\n", ft_printf("|%0*d| \t", width, 123), printf("|%0*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #6\n", ft_printf("|%+0*d| \t", width, 123), printf("|%+0*d| \t", width, 123));
	printf("ft_printf: %d vs %d :printf #7\n", ft_printf("|%+-0*d| \t", width, 123), printf("|%+-0*d| \t", width, 123));

	printf("-------------------------------------BINARY----------------------------------------\n");
	u = 2;
	printf("returns: %d #1\n", ft_printf("|%r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%1r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%4r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%5r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%6r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%7r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-1r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-4r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-5r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-6r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-7r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.1r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.4r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.5r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%.6r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.1r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.4r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.5r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%3.6r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%4.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%5.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%6.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-3.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-4.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-5.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-6.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-7.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-8.2r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-3.3r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-5.4r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-7.5r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-9.6r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-11.7r|\t", u));
	printf("returns: %d #1\n", ft_printf("|%-13.8r|\t", u));
	//while(1);	
	print_binary(63);
	return (0);
}
