/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:05:16 by mait-all          #+#    #+#             */
/*   Updated: 2025/01/19 17:27:52 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}

static void	ft_putstr(char *s, int *count)
{
	if (!s)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (*s)
		ft_putchar(*s++, count);
}

static void	ft_check_format(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (c == 'x' || c == 'X')
		ft_puthex(va_arg(args, unsigned int), c, count);
	else if (c == 'u')
		ft_putunsigned(va_arg(args, unsigned int), count);
	else if (c == 'p')
	{
		ft_putstr("0x", count);
		ft_putaddress(va_arg(args, unsigned long), count);
	}
	else if (c == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (format[1] == '\0')
				return (count);
			ft_check_format(*(format + 1), args, &count);
			format++;
		}
		else
			ft_putchar(*format, &count);
		format++;
	}
	va_end(args);
	return (count);
}
