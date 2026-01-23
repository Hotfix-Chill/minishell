/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:04:12 by abita             #+#    #+#             */
/*   Updated: 2026/01/21 12:55:22 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *line, int i)
{
	while ((line[i] && line[i] == ' ') || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

int	pipe_check(char *line, int *i_ptr, t_token *tok)
{
	int	i;

	i = *i_ptr;
	if (line[i] == '|')
	{
		if (line[i + 1] == '|')
			return (REDIR_ERROR);
		tok->typ = TOKEN_PIPE;
		*i_ptr = i + 1;
		return (REDIR_FOUND);
	}
	return (REDIR_NONE);
}

int	redir_check(char *line, int *i_ptr, t_token *tok)
{
	int	i;

	i = *i_ptr;
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

int	decide_token_type(char *line, int *i_ptr, t_token *tok)
{
	int	i;
	int	res;
	int	res_pipe;

	i = *i_ptr;
	res = redir_check(line, i_ptr, tok);
	if (res == REDIR_ERROR)
		return (-1);
	else if (res == REDIR_FOUND)
		return (EXIT_SUCCESS);
	res_pipe = pipe_check(line, i_ptr, tok);
	if (res_pipe == REDIR_ERROR)
		return (-1);
	else if (res_pipe == REDIR_FOUND)
		return (EXIT_SUCCESS);
	else if (line[i] == '>')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_OUT, \
			*i_ptr = i + 1, EXIT_SUCCESS);
	else if (line[i] == '<')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_IN, \
			*i_ptr = i + 1, EXIT_SUCCESS);
	tok->typ = TOKEN_WORD;
	tok->quote = QUOTE_NORMAL;
	return (EXIT_SUCCESS);
}

int	set_operator_content(t_token *tok)
{
	if (tok->typ == TOKEN_PIPE)
		return (append_str_to_content(tok, "|"));
	if (tok->typ == TOKEN_REDIR)
	{
		if (tok->redir == REDIR_APPEND)
			return (append_str_to_content(tok, ">>"));
		if (tok->redir == REDIR_HEREDOC)
			return (append_str_to_content(tok, "<<"));
		if (tok->redir == REDIR_IN)
			return (append_str_to_content(tok, "<"));
		if (tok->redir == REDIR_OUT)
			return (append_str_to_content(tok, ">"));
	}
	return (EXIT_SUCCESS);
}
