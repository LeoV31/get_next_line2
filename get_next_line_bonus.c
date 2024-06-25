/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:31:41 by lviguier          #+#    #+#             */
/*   Updated: 2024/06/25 15:34:48 by lviguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[256];
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 256)
		return (NULL);
	while (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
	{
		bytes_read = 0;
		bytes_read = read_to_buffer(fd, &buffer[fd]);
		if (bytes_read <= 0 && !buffer[fd])
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	line = get_line(&buffer[fd]);
	return (line);
}
/**
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int     fd;
    int		fd2;
    char    *line1;
    char	*line2;

    if (argc != 3)
	    return (1);
    fd = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);
    if (fd == -1 || fd2 == -1)
    {
        perror("Error opening file");
        return (1);
    }
    line1 = get_next_line(fd);
    line2 = get_next_line(fd2);
    while (line1 != NULL && line2 != NULL)
    {
   	 printf("%s", line1);
	 printf("%s", line2);
	 line1 = get_next_line(fd);
	 line2 = get_next_line(fd2);
    }
    free(line1);
    free(line2);
    close(fd);
    return (0);
}
**/
