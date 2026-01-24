/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:48:17 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 19:16:03 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ifs_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t	count_words(const char *str)
{
	size_t	count;
	size_t	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_ifs_char(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i] && !is_ifs_char(str[i]))
			i++;
	}
	return (count);
}

int	free_split_arrays(t_buffer *buffer)
{
	free_split(buffer->argv);
	free(buffer->no_expand);
	free(buffer->no_split);
	return (EXIT_FAILURE);
}

size_t	count_total_words(t_cmds *cmd)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->no_split && cmd->no_split[i])
			total++;
		else
			total += count_words(cmd->argv[i]);
		i++;
	}
	return (total);
}

int	alloc_arrays(size_t total, t_buffer *buf)
{
	buf->argv = ft_calloc(total + 1, sizeof(char *));
	if (!buf->argv)
		return (EXIT_FAILURE);
	buf->no_expand = ft_calloc(total + 1, sizeof(bool));
	if (!buf->no_expand)
		return (free(buf->argv), EXIT_FAILURE);
	buf->no_split = ft_calloc(total + 1, sizeof(bool));
	if (!buf->no_split)
		return (free(buf->argv), free(buf->no_expand), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
