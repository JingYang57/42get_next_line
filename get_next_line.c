/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiloh <jiloh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:22:47 by jiloh             #+#    #+#             */
/*   Updated: 2024/04/13 17:22:49 by jiloh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join(char *line, char *res)
{
	char	*temp;

	temp = ft_strjoin(line, res);
	free(line);
	return (temp);
}

char	*free_line(char *line)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (*(line + i) && *(line + i) != '\n')
		i++;
	if (!*(line + i))
	{
		free(line);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(line) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (*(line + i))
		*(temp + j++) = *(line + i++);
	free(line);
	return (temp);
}

char	*extract_next_line(char *line)
{
	int		i;
	char	*next_line;

	i = 0;
	if (!*(line + i))
		return (NULL);
	while (*(line + i) && *(line + i) != '\n')
		i++;
	next_line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (*(line + i) && *(line + i) != '\n')
	{
		*(next_line + i) = *(line + i);
		i++;
	}
	if (*(line + i) == '\n' && *(line + i))
		*(next_line + i++) = '\n';
	return (next_line);
}

char	*extract_line(char *line, int fd)
{
	char	*res;
	int		size;

	if (!line)
		line = ft_calloc(1, 1);
	res = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	size = 1;
	while (size > 0)
	{
		size = read(fd, res, BUFFER_SIZE);
		if (size < 0)
		{
			free(res);
			return (NULL);
		}
		res[size] = '\0';
		line = join(line, res);
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(res);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || read(fd, &next_line, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = extract_line(line, fd);
	if (line == NULL)
		return (NULL);
	next_line = extract_next_line(line);
	line = free_line(line);
	return (next_line);
}

// int	main(void)
// {
// 	int fd;

// 	fd = open("test.txt", O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	return (0);
// }