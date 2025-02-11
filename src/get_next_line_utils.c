/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:02:40 by khiidenh          #+#    #+#             */
/*   Updated: 2024/12/03 09:33:45 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++ != '\0')
		length ++;
	return (length);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*news;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	news = (char *) malloc((ft_strlen(s1) * sizeof(char))
			+ (ft_strlen(s2) * sizeof(char)) + 1);
	if (news == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		news[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		news[i] = s2[j];
		i++;
		j++;
	}
	news[i] = '\0';
	return (news);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	character;

	character = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == character)
			return ((char *)(&s[i]));
		i++;
	}
	if (character == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	length;
	char	*dups;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	dups = malloc(length + 1);
	if (dups == NULL)
		return (NULL);
	while (length > 0)
	{
		dups[i] = s[i];
		i++;
		length--;
	}
	dups[i] = '\0';
	return (dups);
}
