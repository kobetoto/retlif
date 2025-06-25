/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login> <mail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/06/25 15:21:35 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 200
#endif

void    filter(char *str, char *filter)
{
        int     i,j,k;
        int     match;
        int     filter_len;

        filter_len = strlen(filter);
        i = 0;
        while (str[i])
        {
                j = 0;
                k = 0;
                match = 1;
                while (filter[j])
                {
                        if(str[i + j] != filter[j])
                        {
                                match = 0;
                                break;
                        }
                        j++;
                }
                if (match)
                {
                        while (k < filter_len)
                        {
                                printf("*");
                                k++;
                        }
                        i += filter_len;
                }
                else 
                {
                        printf("%c",str[i]);
                        i++;
                }
        }
}

int     main(int ac, char **av )
{
        char    buf[BUF_SIZE + 1];
        char    *stock;
        int     capacity;
        int     b_read;
        int     total_len;
        int     i;

        if (ac != 2 || strlen(av[1]) == 0)
                return (1);
        capacity = BUF_SIZE;
        stock = malloc(capacity);
        if (stock == NULL)
                return (perror("Error: "), 1);
        total_len = 0;
        while((b_read = read(0, buf, BUF_SIZE)) > 0)
        {
                if (total_len + b_read > capacity)
                {
                        int new_cap = capacity * 2;
                        while (new_cap < total_len + b_read)
                                new_cap *= 2;
                        char *new_ptr = realloc(stock, new_cap);
                        if (new_ptr == NULL)
                                return (free(stock), perror("Error: "), 1);
                        stock = new_ptr;
                        capacity = new_cap;
                }
                i = 0;
                while(i < b_read)
                {
                        stock[total_len] = buf[i];
                        i++;
                        total_len++;
                }
        }
        if (b_read < 0)
        {
                free(stock);
                perror("Error: ");
                return (1);
        }
        stock[total_len] = '\0';
        filter(stock, av[1]);
        free(stock);
        return (0);
}
