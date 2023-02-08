#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	*resize(char **array, size_t old_len, size_t new_len)
{
	char	*new_array;
	size_t	i;

	new_array = malloc(sizeof(char) * new_len);
	{
		if (new_array == NULL)
			return (NULL);
		i = 0;
		while (i < old_len)
		{
			new_array[i] = (*array)[i];
			i++;
		}
		free(*array);
		(*array) = new_array;
		return (new_array);
	}
}

char	*get_next_line(int fd)
{
	char	c;
	char	*buffer;
	size_t	buff_size;
	size_t	read_char;
	int		reader;

	if (fd < 0)
		return (NULL);
	buff_size = 100;
	buffer = malloc(sizeof(char) * buff_size + 1);
	if (buffer == NULL)
		return (NULL);
	read_char = 0;
	c = 0;
	reader = read(fd, &c, 1);
	if (reader <= 0)
	{
		free(buffer);
		return (NULL);
	}
	while (reader > 0 && c != '\n')
	{
		buffer[read_char] = c;
		read_char++;
		if (read_char >= buff_size)
		{
			resize(&buffer, buff_size, buff_size * 2 + 1);
			buff_size *= 2;
		}
		reader = read(fd, &c, 1);
	}
	if (reader > 0 && c == '\n')
		buffer[read_char] = c;
	buffer[read_char + 1] = 0;
	return (buffer);
}

int main(void)
{
	int fd = open("test.file", O_RDONLY);
	if (fd < 0)
		return 1;
	char * line = get_next_line(fd);
	while (line)
	{
		printf("[%s]\n", line);
		free(line);
		line = get_next_line(fd);
	}
}