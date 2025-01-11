/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:55:07 by quenalla          #+#    #+#             */
/*   Updated: 2024/06/06 17:45:50 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_setting(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (s1[end])
		end++;
	while (s1[start] && (ft_setting(s1[start], set) == 1))
		start++;
	while (end > start && (ft_setting(s1[end - 1], set) == 1))
		end--;
	str = malloc(sizeof(*s1) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
