#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	int		i;
	int		reader;
	char	c;
	char	*buffer;

	i = 0;
	reader = 0;
	buffer = malloc(10000);
	while ((reader = read(fd, &c, 1)) > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
	}
	if ((!buffer[i - 1] && !reader) || reader == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}
