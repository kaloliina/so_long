/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:08:36 by khiidenh          #+#    #+#             */
/*   Updated: 2024/12/03 11:27:49 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(char *remainder, char *buffer)
{
	char	*newremainder;

	if (remainder != NULL)
	{
		newremainder = ft_strjoin(remainder, buffer);
		if (newremainder == NULL)
			return (NULL);
		free(remainder);
		remainder = NULL;
	}
	else
	{
		newremainder = ft_strdup(buffer);
		if (newremainder == NULL)
			return (NULL);
	}
	return (newremainder);
}

static char	*update_buffer(char *remainder, int fd)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (remainder == NULL || ft_strchr(remainder, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, (BUFFER_SIZE));
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		remainder = read_and_store(remainder, buffer);
		if (remainder == NULL)
		{
			free(buffer);
			return (NULL);
		}
	}
	free (buffer);
	return (remainder);
}

static char	*get_remainder(char *line)
{
	char	*newline;
	char	*remainder;

	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		remainder = ft_strdup(newline + 1);
		if (remainder == NULL)
			return (NULL);
		line[newline - line + 1] = '\0';
	}
	else
		remainder = NULL;
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = update_buffer(remainder, fd);
	if (line == NULL)
	{
		free (remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = get_remainder(line);
	if (remainder == NULL && ft_strchr(line, '\n') != NULL)
	{
		free(line);
		return (NULL);
	}
	if (remainder != NULL && remainder[0] == '\0')
	{
		free (remainder);
		remainder = NULL;
	}
	return (line);
}
