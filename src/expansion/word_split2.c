/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:11:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/02 14:33:38 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_split_words(const char *str, t_buffer *buf)
{
	size_t	i;
	size_t	start;
	char	*word;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && is_ifs_char(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_ifs_char(str[i]))
			i++;
		word = ft_substr(str, start, i - start);
		if (!word)
			return (EXIT_FAILURE);
		buf->argv[buf->idx] = word;
		buf->no_expand[buf->idx] = false;
		buf->no_split[buf->idx] = false;
		(buf->idx)++;
	}
	return (EXIT_SUCCESS);
}

int	append_quoted_word(t_cmds *cmd, size_t i, t_buffer *buf)
{
	buf->argv[buf->idx] = ft_strdup(cmd->argv[i]);
	if (!buf->argv[buf->idx])
		return (EXIT_FAILURE);
	buf->no_expand[buf->idx] = false;
	buf->no_split[buf->idx] = true;
	(buf->idx)++;
	return (EXIT_SUCCESS);
}
