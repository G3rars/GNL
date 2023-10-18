#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER 400

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;

	while (str && str[i] != '\0')
    {   
        if (str[i++] =='\n')
            return (i);
	    i++;
    }
	return (i);
}

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)str;
	while (i < n)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	temp = malloc((count * size));
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, (count * size));
	return (temp);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_l;

	dest_l = ft_strlen(dest);
	if (size <= dest_l)
		return (ft_strlen(src) + size);
	i = 0;
	j = dest_l;
	while (src[i] != '\0' && j < size - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest_l + ft_strlen(src));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_l;

	i = 0;
	src_l = ft_strlen(src);
	if (size <= 0)
		return (src_l);
	while (src[i] != 0 && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	ft_strlcat(res, s2, len + 1);
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
        {
            if (str[i] == '\n')
                i++;
			return ((char *)(str + i));
        }
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

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


void get_line(char *save, char **line, int chars_read)
{
    int len;
    char *new;
    if (ft_strlen(*line) >= BUFFER && chars_read != 0)
    {
        new = ft_strjoin(*line, save);
        free(*line);
        *line = new;
        return ;
    }
    len = ft_strlen(save);
    if (len == 0)
        return ;
    *line = malloc((len + 1) * sizeof(char));
    if (!line)
        return ;
    if (!line)
        return ;
    ft_memmove(*line, save, len);
    (*line)[len + 1] = '\0';
}

char *get_next_line(int fd)
{
    static char *save;
    char *line;
    int chars_read;

    line = NULL;
    if (fd < 0 || BUFFER < 0)
        return (NULL);
    if(!save)
        save = malloc((BUFFER + 1) * sizeof(char));
    chars_read = read(fd, save, BUFFER); // -> 14 || -> 2
		get_line(save, &line, chars_read);
    while (chars_read == BUFFER) // no ha terminado de leer
    {
        get_line(save, &line, chars_read);
        if(ft_strchr(line, '\n'))
        {
            line[ft_strlen(line) + 1] = '\0';
            return (line);
        }
        chars_read = read(fd, save, BUFFER);
    } 
    if ((chars_read == 0 || chars_read <= BUFFER) && *save != '\0') // ha leido todo o finalizo su lectura
    {
        get_line(save, &line, chars_read);
        save = ft_strchr(save, '\n');
        return (line);
    }
    return (NULL);
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
     for (size_t i = 0; line != NULL; i++)
    {
         line = get_next_line(fd);
         free(line);
         printf("linea: %s\n", line);
    }
    close(fd);
    return 0;
 }
