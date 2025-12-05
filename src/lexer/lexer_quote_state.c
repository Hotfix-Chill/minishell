/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:43:33 by abita             #+#    #+#             */
/*   Updated: 2025/12/03 21:43:34 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void normal_quote_state(char c, char next_c, int i, t_token *toklist)
{
	if (toklist->quote == QUOTE_NORMAL)
	{
		if (c == '>' && next_c == '>')
		{
			toklist->typ = TOKEN_REDIR;
			toklist->redir = REDIR_APPEND;
			i += 2;
		}
		else if (c == '<' && next_c == '<')
		{
			toklist->typ = TOKEN_REDIR;
			toklist->redir = REDIR_HEREDOC;
			i += 2;
		}
		else if (c == '\'')
		{
			toklist->quote = QUOTE_SINGLE;
			i++;
		}
		else if (c == '\"')
		{
			toklist->quote = QUOTE_DOUBLE;
			i++;
		}
		else if (c == '|')
		{
			toklist->typ = TOKEN_PIPE;
			i++;
		}
		else if (c == '>')
		{
			toklist->typ = TOKEN_REDIR;
			toklist->redir = REDIR_OUT;
			i++;
		}
		else if (c == '<')
		{
			toklist->typ = TOKEN_REDIR;
			toklist->redir = REDIR_IN;
			i++;
		}
		else
			toklist->typ = TOKEN_WORD;
	}
}

// void double_quote_state()
// {

// }
// void single_quote_state()
// {

// }