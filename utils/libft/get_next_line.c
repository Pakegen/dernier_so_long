/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:39:06 by qacjl             #+#    #+#             */
/*   Updated: 2024/09/23 09:19:20 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*ft_next(char *res)
{
	char	*buffer;
	size_t	i;

	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (res[i] == '\0' || res[1] == '\0')
		return (NULL);
	buffer = ft_substr(res, i + 1, ft_strlen(res) - i);
	if (*buffer == '\0')
	{
		free (buffer);
		buffer = NULL;
	}
	res[i + 1] = '\0';
	return (buffer);
}

static char	*ft_read(int fd, char *buffer, char *str)
{
	char	*tmp;
	ssize_t	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		str[byte_read] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		tmp = buffer;
		buffer = ft_strjoin(tmp, str);
		free (tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[LIMIT_FD];
	char		*str;
	char		*res;

	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
	{
		free (str);
		return (NULL);
	}
	if (fd < 0 || read(fd, 0, 0) || fd > LIMIT_FD)
	{
		free (buffer[fd]);
		free (str);
		buffer[fd] = NULL;
		str = NULL;
		return (NULL);
	}
	res = ft_read(fd, buffer[fd], str);
	free (str);
	str = NULL;
	if (!res)
		return (NULL);
	buffer[fd] = ft_next(res);
	return (res);
}

/*int	main()
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}*/
