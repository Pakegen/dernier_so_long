/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:25:16 by quenalla          #+#    #+#             */
/*   Updated: 2024/09/23 10:00:15 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_pourcent(void)
{
	write(1, "%", 1);
	return (1);
}

static int	ft_format(va_list args, const char str)
{
	int	len;

	len = 0;
	if (str == 'c')
		len += ft_printchar(va_arg(args, int));
	else if (str == 's')
		len += ft_print_s(va_arg(args, char *));
	else if (str == 'i' || str == 'd')
		len += ft_print_d(va_arg(args, int));
	else if (str == 'u')
		len += ft_print_u(va_arg(args, unsigned int));
	else if (str == 'x')
		len += ft_print_x(va_arg(args, unsigned int));
	else if (str == 'X')
		len += ft_print_maj_x(va_arg(args, unsigned int));
	else if (str == 'p')
		len += ft_print_p(va_arg(args, unsigned long int));
	else if (str == '%')
		len += ft_pourcent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
				len += ft_format(args, str[++i]);
		else
			len += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
