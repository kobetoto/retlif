#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	filter(char *buf, int len, char *filter)
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
	char		buf[1024];
	char		tmp[2048]; // buffer temporaire = residu + buf
	char		residue[64]; // taille max d’un filtre raisonnable
	int			read_len;
	int			filter_len;
	int			residue_len = 0;

	if (ac != 2 || strlen(av[1]) == 0)
		return (1);
	filter_len = strlen(av[1]);

	while ((read_len = read(0, buf, sizeof(buf))) > 0)
	{
		// On copie residue + buf dans tmp
		memcpy(tmp, residue, residue_len);
		memcpy(tmp + residue_len, buf, read_len);

		// Appel sur le buffer combiné
		filter(tmp, residue_len + read_len, av[1]);

		// Met à jour la nouvelle residue (à la fin de buf)
		if (filter_len - 1 < read_len)
			memcpy(residue, buf + read_len - (filter_len - 1), filter_len - 1);
		else
			memcpy(residue, tmp + residue_len + read_len - (filter_len - 1), filter_len - 1);
		residue_len = filter_len - 1;
	}
	if (read_len < 0)
	{
		perror("Error: ");
		return (1);
	}
	return (0);
}

