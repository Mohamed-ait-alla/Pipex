/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:31:26 by mait-all          #+#    #+#             */
/*   Updated: 2024/11/21 15:32:19 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
		*count += write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		*count += write(1, "-", 1);
		ft_putnbr(-nb, count);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
	else
		*count += write(1, &("0123456789"[nb]), 1);
}

void	ft_puthex(unsigned int nb, char format, int *count)
{
	char	*hex;

	hex = NULL;
	if (format == 'x')
		hex = LOWER_HEX;
	else if (format == 'X')
		hex = UPPER_HEX;
	if (nb < 16)
		*count += write(1, &hex[nb], 1);
	else
	{
		ft_puthex(nb / 16, format, count);
		ft_puthex(nb % 16, format, count);
	}
}

void	ft_putunsigned(unsigned int nb, int *count)
{
	if (nb < 10)
		*count += write(1, &("0123456789"[nb]), 1);
	else
	{
		ft_putunsigned(nb / 10, count);
		ft_putunsigned(nb % 10, count);
	}
}

void	ft_putaddress(unsigned long address, int *count)
{
	if (address < 16)
		*count += write(1, &LOWER_HEX[address], 1);
	else
	{
		ft_putaddress(address / 16, count);
		ft_putaddress(address % 16, count);
	}
}
