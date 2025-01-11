/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:10:03 by quenalla          #+#    #+#             */
/*   Updated: 2024/09/23 09:49:40 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"


int	ft_print_u(unsigned int n)
{
	char	nbr;
	int		contador;

	contador = 0;
	if (n == 0)
		return (ft_printchar('0'));
	if (n > 9)
		contador += ft_print_u(n / 10);
	nbr = (n % 10) + '0';
	contador += ft_printchar(nbr);
	return (contador);
}
