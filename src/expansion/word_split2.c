/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:11:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 15:10:13 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 9) Split an unquoted string into words and append them to the new argv. */
int	fill_split_words(const char *str, char **argv, bool *no_expand,
		bool *no_split, size_t *idx)
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
		argv[*idx] = word;
		no_expand[*idx] = false;
		no_split[*idx] = false;
		(*idx)++;
	}
	return (EXIT_SUCCESS);
}


// 8)Copy a quoted word as-is into the rebuilt argv and mark it no_split. */
int	append_quoted_word(t_cmds *cmd, size_t i, char **argv,
		bool *no_expand, bool *no_split, size_t *idx)
{
	argv[*idx] = ft_strdup(cmd->argv[i]);
	if (!argv[*idx])
		return (EXIT_FAILURE);
	no_expand[*idx] = false;
	no_split[*idx] = true;
	(*idx)++;
	return (EXIT_SUCCESS);
}

