/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:39:35 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 16:44:04 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "get_next_line.h"

char	*ft_line(char *line, int j, int *i, int *bytes)
{
	if (j)
	{
		line[j] = '\0';
		return (line);
	}
	else
	{
		free(line);
		line = NULL;
		*i = 0;
		*bytes = 0;
		return (NULL);
	}
	return ;
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	int			j;
	static int	i = 0;
	static int	bytes = 0;

	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(10000, 1);
	if (!line)
		return (NULL);
	while (1)
	{
		if (i >= bytes)
		{
			i = 0;
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (bytes < 0)
					return (free(line), perror("Error"), NULL);
				break ;
			}
		}
		line[j++] = buf[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	return (ft_line(line, j, &i, &bytes));
} */
