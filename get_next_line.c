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
#define BUFFER 100

int counter(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        i++;
    str[i] = '\0';
    return(i);
}

char *get_next_line(int fd)
{
    static char *buff;
    char *res;
    int len_line;
    int i;
    
        buff = malloc(BUFFER * sizeof(char));
        if (!buff)
            return (NULL);
        read(fd, buff, BUFFER);

    len_line = counter(buff);
    i = 0;
    res = malloc(i * sizeof(char));
    while (len_line--)
        res[i++] = *buff++;
    res[i] = '\0';
    buff++;
    return (res);
}



int main()
{
   int fd;
   fd = open("text.txt", O_RDONLY);
   char *res;

    res = get_next_line(fd);
    printf("\nlinea[1] = %s\n", res);
     res = get_next_line(fd);
     free(res);
    printf("\nlinea[2] = %s\n", res);
     res = get_next_line(fd);
     free(res);
    printf("\nlinea[3] = %s\n", res);
    free(res);
   close(fd);
   return (0);
}