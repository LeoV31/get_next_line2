/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:31:41 by lviguier          #+#    #+#             */
/*   Updated: 2024/06/25 12:56:55 by lviguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*result;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy (result, s, ft_strlen(s) + 1);
	return (result);
}

char	*get_line(char **buffer)
{
	char	*new_line_pos;
	char	*temp;
	char	*line;

	if (!*buffer)
		return (NULL);
	new_line_pos = ft_strchr(*buffer, '\n');
	if (new_line_pos)
	{
		line = ft_strdup(*buffer);
		line[new_line_pos - *buffer + 1] = '\0';
		temp = ft_strdup(new_line_pos + 1);
		free(*buffer);
		*buffer = temp;
	}
	else
		line = ft_strdup(*buffer);
	if (**buffer == '\0' || !new_line_pos)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

int	read_to_buffer(int fd, char **buffer)
{
	char	*new_buffer;
	char	*temp;
	int		bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (-1);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (bytes_read);
	}
	temp[bytes_read] = '\0';
	if (*buffer)
		new_buffer = ft_strjoin(*buffer, temp);
	else
		new_buffer = ft_strdup(temp);
	free(*buffer);
	*buffer = new_buffer;
	free(temp);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		bytes_read = 0;
		bytes_read = read_to_buffer(fd, &buffer);
		if (bytes_read <= 0 && !buffer)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	line = get_line(&buffer);
	return (line);
}
/**
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc != 2)
	    return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    printf("%i\n", fd);
    while ((line = get_next_line(fd)) != NULL)
    {
   	 printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
**/
