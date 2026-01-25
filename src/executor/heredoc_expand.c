/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 02:34:22 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 14:27:34 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_expand(t_data *data, char *line, int fd)
{
	char	*new_line;

	new_line = split_dollar(data, line);
	if (!new_line)
		cleanup(data, ERROR);
	ft_putendl_fd(new_line, fd);
	free(new_line);
	return ;
}
