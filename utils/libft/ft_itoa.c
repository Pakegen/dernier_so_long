/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:30 by qacjl             #+#    #+#             */
/*   Updated: 2024/06/05 15:22:58 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_compteur(long int nb)
{
	long	len;

	len = 1;
	if (1 > nb)
		return (len);
	while (nb >= 10 && len++ >= 0)
		nb = nb / 10;
	return (len);
}

void	ft_alt_neg(char *str, long int nb)
{
	long int	compteur;
	int			i;

	i = 0;
	str[i++] = '-';
	compteur = 1;
	while (compteur <= nb)
		compteur = compteur * 10;
	while (compteur > 1)
	{
		compteur = compteur / 10;
		str[i] = nb / compteur + '0';
		nb = nb % compteur;
		i++;
	}
}

void	ft_alt(char *str, long int nb)
{
	long int	compteur;
	int			i;

	i = 0;
	compteur = 1;
	while (compteur <= nb)
		compteur = compteur * 10;
	while (compteur > 1)
	{
		compteur = compteur / 10;
		str[i] = nb / compteur + '0';
		nb = nb % compteur;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			len;
	int			neg;

	neg = 1;
	nb = n;
	len = 0;
	if (nb < 0 && neg-- >= 1 && len++ >= 0)
		nb = -nb;
	len = len + ft_compteur(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (neg == 0)
		ft_alt_neg(str, nb);
	else if (nb == 0)
		str[0] = '0';
	else if (nb >= 1)
		ft_alt(str, nb);
	str[len] = '\0';
	return (str);
}
