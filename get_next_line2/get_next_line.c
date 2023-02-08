# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!new_str)
		return (NULL);
	while (str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	free(str1);
	while(*str2)
	{
		new_str[i++] = *str2;
		if (*str2++ == '\n')
			break ;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	clear_mem(char *buffer)
{
	int	i;
	int	next_line;
	int	j;

	i = 0;
	j = 0;
	next_line = 0;
	while (buffer[i])
	{
		if (next_line)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			next_line = 1;
		buffer[i++] = '\0';
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		while(buffer[i])
			buffer[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, buffer);
		if (clear_mem(buffer))
			break ;
	}
	return (line);
}