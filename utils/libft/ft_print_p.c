/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:20:24 by quenalla          #+#    #+#             */
/*   Updated: 2024/09/23 10:00:15 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	lenphexa(unsigned long int p)
{
	int	len;

	len = 0;
	while (p != 0)
	{
		len++;
		p = p / 16;
	}
	return (len);
}

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_printchar(str[i++]);
}

static void	ft_put_phexa(unsigned long int p)
{
	if (p >= 16)
	{
		ft_put_phexa(p / 16);
		ft_put_phexa(p % 16);
	}
	else
	{
		if (p < 10)
			ft_printchar(p + '0');
		else
			ft_printchar(p - 10 + 'a');
	}
}

int	ft_print_p(unsigned long int p)
{
	int	len;

	if (p == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	len = 0;
	len += ft_printchar('0');
	len += ft_printchar('x');
	len += lenphexa(p);
	ft_put_phexa(p);
	return (len);
}
