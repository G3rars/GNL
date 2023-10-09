#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
   int fd;
   char buf[101];
   int chars_read;
   
   fd = open("text.txt", O_RDONLY);

   while ((chars_read = read(fd, buf, 100)))
   { 
       buf[chars_read] = '\0';
       printf("\nleido: %s", buf);
   }
   return 0;
}