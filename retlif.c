
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void    filter(char *buf, char *filter)
{
        int     i, j ,k;
        int     fltr_len, match;

        i = 0;
        fltr_len = strlen(filter);
        while (buf[i])
        {
                j = 0;  
                k = 0;  
                match = 1;
                while (filter[j])
                {
                        if(buf[i + j] != filter[j])
                        {
                                match = 0;
                                break;  
                        }
                        j++;    
                }
                if (match == 1)
                {
                        while(k < fltr_len)
                        {
                                printf("*");
                                k++;
                        }       
                        i += fltr_len;
                }       
                else    
                {
                        printf("%c",buf[i]);
                        i++;    
                }       
        }       
}


int     main(int ac, char **av)
{
        int     byte_read;
        char    *buf;
        if (ac != 2)
                return (1);
        if (strlen(av[1]) == 0)
                return (1);
        buf = malloc(7000);
        if (buf == NULL)
        {
                perror("Error: ");
                return (1);
        }
        byte_read = read(0, buf, 7000);
        if (byte_read < 0)
        {
                perror("Error: ");
                return (1);

        }
        filter(buf, av[1]);
        free(buf);
        return (0);
}
