/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:30:46 by quenalla          #+#    #+#             */
/*   Updated: 2024/09/23 09:54:04 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_len_hexa(unsigned int i)
{
	int	len;

	len = 0;
	while (i != 0)
	{
		len++;
		i = i / 16;
	}
	return (len);
}

static void	ft_puthexa(unsigned int i)
{
	if (i >= 16)
	{
		ft_puthexa(i / 16);
		ft_puthexa(i % 16);
	}
	else
	{
		if (i < 10)
			ft_printchar(i + '0');
		else
			ft_printchar(i - 10 + 'a');
	}
}

int	ft_print_x(unsigned int i)
{
	int	len;

	if (i == 0)
		return (ft_printchar('0'));
	len = ft_len_hexa(i);
	ft_puthexa(i);
	return (len);
}
