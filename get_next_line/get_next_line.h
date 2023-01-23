#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>


char	*get_next_line(int fd);
void	*resize(char **array, size_t old_len, size_t new_len);

#endif