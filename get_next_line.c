/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:28:18 by jergonza          #+#    #+#             */
/*   Updated: 2023/10/04 14:28:21 by jergonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER 500 // Tamaño de búfer de lectura

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void ft_realloc(char **res, char *save)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!*res)
    {
        *res = malloc(BUFFER + 1 * sizeof(char));
        if (!res)
            return ;
        while (i <= BUFFER)
        {   
            if (save[i] == '\n')
            {
                (*res)[i] = '\n';
                break ;
            }
            (*res)[i] = save[i];
            i++;
        }
        return ;
    }
    i = ft_strlen(res[0]);
    new = malloc((i + BUFFER) * sizeof(char));
    if (!new)
        return ;
     while ((*res)[j] != '\0')
    {
        new[j] = (*res)[j];
        j++;
    }
    j = 0;
    while (save[j] != '\0')
    {
        new[i++] = save[j++];
    }
    new[i] = '\0';
    free(*res);
    *res = new;
}

char *get_next_line(int fd)
{
    static char save[BUFFER];
    char *res;

    res = NULL;
    if (fd < 0 || BUFFER <= 0 || read(fd, &save, 0) < 0)
        return (NULL);
    while (read(fd, save, BUFFER) > 0)
    {
        ft_realloc(&res, save);
         if (ft_strchr(res, '\n'))
        {
            res[ft_strlen(res) + 1] = '\0';
            printf("Antes de ft_memmove - save: %s, res: %s\n", save, res);
        ft_memmove(save, res, ft_strlen(res) + 1);

            return (res);
        }
    }
    printf("save = %s", save);
    return(res);
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
    line = get_next_line(fd);
    printf("linea: %s\n", line);
     line = get_next_line(fd);
    printf("linea: %s\n", line);
    free(line);
    

    close(fd);
    return 0;
}
