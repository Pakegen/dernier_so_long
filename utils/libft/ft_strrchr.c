/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:07:52 by quenalla          #+#    #+#             */
/*   Updated: 2024/05/31 16:27:42 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			str = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
		str = (char *)s;
	return (str);
}
