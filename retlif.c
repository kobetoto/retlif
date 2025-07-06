/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:46:46 by thodavid          #+#    #+#             */
/*   Updated: 2025/07/03 14:02:59 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#ifndef BUF_SIZE
#define BUF_SIZE 2
#endif

void    filter(char *str, char *filter )
{
        int     i,j,k;
        int     len;
        int     match;

        len = strlen(filter);
        i = 0;
        while (str[i])
        {
                j = 0;
                match = 1;
                while (filter[j])
                {
                        if ( !str[i + j] || str[i +j] != filter[j])
                        {
                                match = 0;
                                break;
                        }
                        j++;
                }
                k = 0;
                if (match)
                {
                        while(k < len)
                        {
                                printf("*");
                                k++;
                        }
                        i += len;
                }
                else
                {
                        printf("%c",str[i]);
                        i++;
                }

        }
}


int     main(int ac, char **av)
{
        char    buf[BUF_SIZE +1];
        char    *stock;
        int     capacity;
        int     total_len;
        int     b_read;
        int     i;

        if (ac != 2 || (strlen(av[1]) == 0))
                return (1);

        capacity = BUF_SIZE +1;
        stock = malloc(capacity);
        if (stock == NULL)
                return (perror("Error: "), (1));
        total_len = 0;

        while ((b_read = read(0, buf, BUF_SIZE)) > 0)
        {
                if (total_len + b_read + 1 > capacity)
                {
                        int     new_cap = capacity*2;
                        while (total_len + b_read + 1 > new_cap)
                                new_cap *= 2;
                        char *new_ptr = realloc(stock, new_cap);
                        if (new_ptr == NULL)
                                return (free(stock), perror("Error: "), (1));
                        stock = new_ptr;
                        capacity = new_cap;
                }
                buf[b_read] = '\0';
                i = 0;
                while(i < b_read)
                {
                        stock[total_len] = buf[i];
                        total_len++;
                        i++;
                }
        }
        if (b_read < 0)
                return (free(stock), perror("Error: "), (1));
        stock[total_len] = '\0';
        filter(stock, av[1]);
        free(stock);
        return (0);
}
