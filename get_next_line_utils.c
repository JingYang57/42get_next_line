/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiloh <jiloh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:23:12 by jiloh             #+#    #+#             */
/*   Updated: 2024/04/13 17:23:15 by jiloh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = -1;
	while (++i < n)
		*(ptr + i) = 0;
	s = ptr;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > 2147483647 / size)
		return (NULL);
	ptr = (void *) malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*(s + length) != '\0')
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = ft_strlen(s);
	i = -1;
	res = (char *)s;
	while (++i <= len)
		if (*(res + i) == (char)c)
			return (res + i);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		totallen;
	int		i;
	int		j;
	char	*res;

	totallen = ft_strlen(s1) + ft_strlen(s2);
	res = (char *) malloc(sizeof(char) * (totallen + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
