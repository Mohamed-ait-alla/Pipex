/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:18:47 by mait-all          #+#    #+#             */
/*   Updated: 2024/11/21 15:33:51 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define UPPER_HEX "0123456789ABCDEF"
# define LOWER_HEX "0123456789abcdef"
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_putnbr(int nb, int *count);
void	ft_puthex(unsigned int nb, char format, int *count);
void	ft_putunsigned(unsigned int nb, int *count);
void	ft_putaddress(unsigned long address, int *count);

#endif