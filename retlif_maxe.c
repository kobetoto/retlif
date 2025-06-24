#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void    filter(char *buf, int len, char *filter)
{
	int	i, j, k;
	int	match;
	int	filter_len;

	filter_len = strlen(filter);
	i = 0;
	while (i < len)
	{
		match = 1;
		j = 0;
		while (filter[j])
		{
			if (i + j >= len || buf[i + j] != filter[j])
			{
				match = 0;
				break;
			}
			j++;
		}
		if (match)
		{
			k = 0;
			while (k < filter_len)
			{
				printf("*");
				k++;
			}
			i += filter_len;
		}
		else
		{
			printf("%c", buf[i]);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	char	buf[1024];
	int		read_len;

	if (ac != 2 || strlen(av[1]) == 0)
		return (1);

	while ((read_len = read(0, buf, sizeof(buf))) > 0)
		filter(buf, read_len, av[1]);

	if (read_len < 0)
	{
		perror("Error: ");
		return (1);
	}
	return (0);
}
