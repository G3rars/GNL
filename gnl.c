#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER 5000

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
    		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

void ft_move(char *save, char **res, int *i)
{
    int j;
    char *new;

    j = 0;
    if (!*res)
    {
        *res = malloc((BUFFER + 1) * sizeof(char));
        if (!*(res))
        return ;
        while (save[j] != '\0' && save[j] != '\n')
        {
            (*res)[*i] = save[j++];
            (*i)++;
        }
        (*res)[*i] = '\0';
        return ;
    }
    new = malloc((ft_strlen(*res) + BUFFER) + 1 * sizeof(char));
    while ((*res)[j] != '\0' && (*res)[j] != '\n')
    {
        new[j] = (*res)[j];
        j++;
    }
    j = 0;
     while (save[j] != '\0' && save[j] != '\n')
    {
        new[*i] = save[j];
        j++;
        (*i)++;
    }
    new[*i] = '\0';
    free(*res);
    *res = new;
}

char *get_next_line(int fd)
{
    static char *save; // par
    char *res; 
    int i;
    int chars;

    i = 0;
    res = NULL;
    if(!save)
        save = malloc(BUFFER * sizeof(char));
    if (save)
        ft_move(save, &res, &i);
    while (!ft_strchr(save, '\n'))
    {
        read(fd, save, BUFFER);
        ft_move(save, &res, &i);
    }
    printf("\nchars = %d\n", chars);
    save = ft_strchr(save, '\n') + 1;
    return (res);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
    char *line;
    for (size_t i = 0; i < 5; i++)
    {
         line = get_next_line(fd);
        printf("linea: %s\n", line);
    }
    close(fd);
    return 0;
 }
