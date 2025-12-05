/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:26:58 by craabe            #+#    #+#             */
/*   Updated: 2025/09/17 15:40:19 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	g_bytes_printed = 0;

static void	ft_write_arg(char type, va_list arg_list)
{
	ssize_t	bytes_printed_temp;

	bytes_printed_temp = g_bytes_printed;
	if (type == '%')
		g_bytes_printed += ft_print_char('%');
	else if (type == 'c')
		g_bytes_printed += ft_print_char(va_arg(arg_list, int));
	else if (type == 's')
		g_bytes_printed += ft_print_str(va_arg(arg_list, char *));
	else if (type == 'd' || type == 'i')
		g_bytes_printed += ft_print_int(va_arg(arg_list, int));
	else if (type == 'u')
		g_bytes_printed += ft_print_uns_int(va_arg(arg_list, unsigned int));
	else if (type == 'p')
		g_bytes_printed += ft_print_pt(va_arg(arg_list, void *));
	else if (type == 'x')
		g_bytes_printed += ft_print_hex(va_arg(arg_list, unsigned int), 0);
	else if (type == 'X')
		g_bytes_printed += ft_print_hex(va_arg(arg_list, unsigned int), 1);
	if (g_bytes_printed < bytes_printed_temp)
		g_bytes_printed = -1;
}

static void	ft_write_form_string(char *str, va_list arg_list)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && g_bytes_printed != -1)
	{
		if (str[i] != '%')
		{
			if (ft_putchar_fd(str[i], 1) != -1)
			{
				g_bytes_printed++;
				i++;
			}
			else
				g_bytes_printed = -1;
		}
		else if (str[i] == '%')
		{
			ft_write_arg(str[i + 1], arg_list);
			i += 2;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;

	g_bytes_printed = 0;
	va_start(arg_list, format);
	ft_write_form_string((char *)format, arg_list);
	va_end(arg_list);
	return ((int)g_bytes_printed);
}

// #include <stdio.h>
// #include <limits.h>
// #include <stdlib.h>
// #include "ft_printf.h"

// int main(void)
// {
//     int ret_std, ret_ft;

//     // --- CHAR ---
//     ret_std = printf("STD: %c\n", 'A');
//     ret_ft  = ft_printf("FT : %c\n", 'A');
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- STRING ---
//     ret_std = printf("STD: %s\n", "Hello, world!");
//     ret_ft  = ft_printf("FT : %s\n", "Hello, world!");
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     ret_std = printf("STD: %s\n", (char *)NULL);
//     ret_ft  = ft_printf("FT : %s\n", (char *)NULL);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- DECIMAL / INT ---
//     ret_std = printf("STD: %d %i\n", 42, -42);
//     ret_ft  = ft_printf("FT : %d %i\n", 42, -42);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     ret_std = printf("STD: %d\n", INT_MAX);
//     ret_ft  = ft_printf("FT : %d\n", INT_MAX);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     ret_std = printf("STD: %d\n", INT_MIN);
//     ret_ft  = ft_printf("FT : %d\n", INT_MIN);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- UNSIGNED ---
//     ret_std = printf("STD: %u\n", 0);
//     ret_ft  = ft_printf("FT : %u\n", 0);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     ret_std = printf("STD: %u\n", UINT_MAX);
//     ret_ft  = ft_printf("FT : %u\n", UINT_MAX);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- HEX lower ---
//     ret_std = printf("STD: %x\n", 3735928559u); // 0xDEADBEEF
//     ret_ft  = ft_printf("FT : %x\n", 3735928559u);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- HEX upper ---
//     ret_std = printf("STD: %X\n", 3735928559u);
//     ret_ft  = ft_printf("FT : %X\n", 3735928559u);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- POINTER ---
//     int x = 42;
//     ret_std = printf("STD: %p\n", &x);
//     ret_ft  = ft_printf("FT : %p\n", &x);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     ret_std = printf("STD: %p\n", NULL);
//     ret_ft  = ft_printf("FT : %p\n", NULL);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- MIXED FORMAT ---
//     ret_std = printf("STD: Hello %s, number=%d, hex=%X, ptr=%p!\n",
//                      "student", -12345, 48879, &x);
//     ret_ft  = ft_printf("FT : Hello %s, number=%d, hex=%X, ptr=%p!\n",
//                      "student", -12345, 48879, &x);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- EDGE: INT_MIN in hex (check unsigned promotion) ---
//     ret_std = printf("STD: %x\n", INT_MIN);
//     ret_ft  = ft_printf("FT : %x\n", INT_MIN);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     // --- EDGE: ULONG_MAX as pointer ---
//     ret_std = printf("STD: %p\n", (void *)ULONG_MAX);
//     ret_ft  = ft_printf("FT : %p\n", (void *)ULONG_MAX);
//     printf("Return values: std=%d, ft=%d\n\n", ret_std, ret_ft);

//     return (0);
// }
