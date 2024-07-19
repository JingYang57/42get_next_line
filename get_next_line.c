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

size_t  ft_strlen(const char *s)
{
        size_t  length;

        length = 0;
        while (*(s + length) != '\0')
                length++;
        return (length);
}

char    *ft_strdup(const char *s1)
{
        int		length;
        int		i;
        char    *dup;

        length = ft_strlen(s1);
        dup = (char *)malloc(length + 1 * sizeof(char));
        if (dup == NULL)
                return (NULL);
        i = 0;
        while (i < length)
        {
                dup[i] = s1[i];
                i++;
        }
        dup[i] = '\0';
        return (dup);
}

char    *ft_strchr(const char *s, int c)
{
        size_t  i;
        size_t  len;
        char    *res;

        len = ft_strlen(s);
        i = -1;
        res = (char *)s;
        while (++i <= len)
                if (*(res + i) == (char)c)
                        return (res + i);
        return (NULL);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        unsigned int    totallen;
        unsigned int    i;
        char                    *res;

        if (!s1 || !s2)
                return (0);
        totallen = ft_strlen(s1) + ft_strlen(s2);
        res = (char *) malloc(sizeof(char) * (totallen + 1));
        if (res == NULL)
                return (NULL);
        i = -1;
        while (++i < ft_strlen(s1))
                *(res + i) = *(s1 + i);
        while (i < totallen)
        {
                *(res + i) = *s2;
                s2++;
                i++;
        }
        *(res + i) = '\0';
        return (res);
}

char	*join(char *line, char *res)
{
	char	*temp;

	temp = ft_strjoin(line, res);
	if (temp == NULL)
		return (NULL);
	free(line);
	return temp;
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
	temp = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	i++;
	j = 0;
	while (*(line + i))
		*(temp + j++) = *(line + i++);
	free(line);
	return (temp);

	// char	*new_line_pos;
	// char	*temp;

	// new_line_pos = ft_strchr(line, '\n');
	// if (!new_line_pos)
	// {
	// 	free(line);
	// 	return (NULL);
	// }
	// temp = ft_strdup(new_line_pos + 1);
	// free(line);
	// return (temp);
}

char	*extract_next_line(char *line)
{
	int		i;
	char	*next_line;
	
	i = 0;
	if(!line[i])
		return (NULL);
	while (*(line + i) && *(line + i) != '\n')
		i++;
	next_line = malloc((i + 2) * sizeof(char));
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
		line = malloc(1);
	res = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (res == NULL)
		return (NULL);
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
			break;
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

int	main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	return (0);
}