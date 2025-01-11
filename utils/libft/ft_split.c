/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:30:34 by quenalla          #+#    #+#             */
/*   Updated: 2024/06/03 12:56:05 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	**ft_error(char **str)
{
	size_t	i2;

	i2 = 0;
	while (str[i2])
	{
		free(str[i2]);
		i2++;
	}
	free(str);
	return (NULL);
}

size_t	ft_count_word(char const *s, char c)
{
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		if (s[index] == c)
			index++;
		else
		{
			i++;
			while (s[index] && (s[index] != c))
				index++;
		}
	}
	return (i);
}

char	*ft_word_dup(char *word, size_t wlen, char const *s, int i)
{
	size_t	k;

	k = 0;
	while (k < wlen)
	{
		word[k] = s[i + k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_word(char **str, size_t number_word, char const *s, char c)
{
	size_t	i1;
	size_t	i2;
	size_t	i3;
	size_t	wlen;

	i1 = 0;
	i2 = 0;
	wlen = 0;
	while (s[i1] && i2 < number_word)
	{
		while (s[i1] && s[i1] == c)
			i1++;
		i3 = i1;
		while (s[i1] && s[i1++] != c)
			wlen++;
		str[i2] = malloc((wlen +1));
		if (str[i2] == NULL)
			return (ft_error(str));
		ft_word_dup(str[i2], wlen, s, i3);
		wlen = 0;
		i2++;
	}
	str[i2] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	number_word;
	char	**str;

	number_word = ft_count_word(s, c);
	str = malloc(sizeof(char *) * (number_word + 1));
	if (str == NULL)
		return (NULL);
	str[number_word] = NULL;
	if (!ft_word(str, number_word, s, c))
		return (NULL);
	return (str);
}
