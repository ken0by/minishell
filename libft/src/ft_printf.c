/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:16:06 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/03/27 15:43:14 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_flags(va_list a, int *r, char c)
{
	if (c == 'c')
		*r += ft_putchar_fd(va_arg(a, int), 1);
	else if (c == 's')
		*r += ft_putstr_fd(va_arg(a, char *), 1);
	else if (c == 'd' || c == 'i')
		*r += ft_putnbr_fd(va_arg(a, int), 1);
	else if (c == 'u')
		*r += ft_putnbr_base(va_arg(a, int), "0123456789");
	else if (c == 'p')
	{	
		*r += ft_putstr_fd("0x", 1);
		*r += ft_putnbr_base_void(va_arg(a, unsigned long), "0123456789abcdef");
	}
	else if (c == 'x')
		*r += ft_putnbr_base(va_arg(a, int), "0123456789abcdef");
	else if (c == 'X')
		*r += ft_putnbr_base(va_arg(a, int), "0123456789ABCDEF");
	else if (c == '%')
		*r += ft_putchar_fd('%', 1);
}

int	ft_printf(const char *str, ...)
{
	va_list		a;
	char		*c;
	size_t		i;
	int			r;

	i = 0;
	r = 0;
	c = (char *)str;
	va_start(a, str);
	while (c && i < ft_strlen(str))
	{
		if (*c != '%')
			r += ft_putchar_fd(*c, 1);
		else if (*c == '%')
		{
			c++;
			ft_flags(a, &r, *c);
			i++;
		}
		c++;
		i++;
	}
	va_end(a);
	return (r);
}
