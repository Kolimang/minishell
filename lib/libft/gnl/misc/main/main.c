/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:41:52 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/08 16:03:55 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDWR);
	if (!fd)
		return (printf("Le fichier n'a pas pu être ouvert\n"), EXIT_FAILURE);
	line = "";
	i = -1;
	while (line)
	{
		line = NULL;
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
}

/*


# include <limits.h>  // required for OPEN_MAX constant
# include <unistd.h>  // required; read & close functions
# include <stdio.h>	  // for constant FOPEN_MAX
# include <stdlib.h>  // malloc(), free(), macro EXIT_FAILURE
# include <fcntl.h>   // for the main(): open() function, O_RDWR argument
# include <sys/errno.h> // debugging

cc *.c -Wall -Wextra -Werror -fsanitize=address -g -D BUFFER_SIZE=2147483647

system("leaks a.out");

*/
