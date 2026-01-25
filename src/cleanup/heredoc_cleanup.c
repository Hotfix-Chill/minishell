/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:28:27 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 22:04:11 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->heredoc.count)
	{
		unlink(data->heredoc.files[i++]);
		if (VERBOSE)
			printf("HEREDOC FILE %s DELETED\n", data->heredoc.files[i - 1]);
	}
	free_split(data->heredoc.files);
	ft_memset(&data->heredoc, 0, sizeof(t_heredoc));
	return ;
}
