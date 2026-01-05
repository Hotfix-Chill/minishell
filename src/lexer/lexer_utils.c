/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:04:12 by abita             #+#    #+#             */
/*   Updated: 2025/12/09 17:04:13 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *line, int i)
{
	while ((line[i] && line[i] == ' ') || (line[i] >= 9 && line[i] <= 13))
			i++;
	return (i);
}

int redir_check(char *line, int *i_ptr, t_token *tok)
{
	int		i;
	char	next_c;

	i = *i_ptr;
	next_c = line[i + 1];
	if (line[i] == '>' && line[i + 1] == '>')
	{
		if (line[i + 2] == '>')
			return (REDIR_ERROR);
		tok->typ = TOKEN_REDIR;
		tok->redir = REDIR_APPEND;
		*i_ptr = i + 2;
		return (REDIR_FOUND);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		if (line[i + 2] == '<')
			return (REDIR_ERROR);
		tok->typ = TOKEN_REDIR;
		tok->redir = REDIR_HEREDOC;
		*i_ptr = i + 2;
		return (REDIR_FOUND);
	}
	return (REDIR_NONE);
}
