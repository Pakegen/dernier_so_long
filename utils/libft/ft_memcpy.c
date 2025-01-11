/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:56:47 by quenalla          #+#    #+#             */
/*   Updated: 2024/06/05 14:15:31 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d1;
	char		*s1;

	i = 0;
	d1 = (char *)dest;
	s1 = (char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > i)
	{
		d1[i] = s1[i];
		i++;
	}
	return (dest);
}
