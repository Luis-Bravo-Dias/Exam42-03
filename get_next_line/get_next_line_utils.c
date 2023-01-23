#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

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