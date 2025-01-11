/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:38:47 by qacjl             #+#    #+#             */
/*   Updated: 2024/09/26 12:34:22 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			k;
	char			*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		str = malloc(1);
	else if (len > (ft_strlen(s) - start))
		str = malloc((ft_strlen(s) - start) + 1);
	else
		str = malloc(len + 1);
	if (str == NULL)
		return (0);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (i >= start && k < len)
			str[k++] = (char)s[i];
		i++;
	}
	str[k] = '\0';
	return (str);
}
