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
#define BUFFER 500 // Tamaño de búfer de lectura

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
        while (i <= BUFFER && save[i] != '\n')
        {
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
    while (save[j] != '\0' && save[j] != '\n')
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
        ft_realloc(&res, save);
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
