/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:50 by abita             #+#    #+#             */
/*   Updated: 2025/11/19 15:43:52 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	A parser is divided into two parts: a Lexical Analyzer or Lexer takes the input characters and
puts the characters together into words called tokens,
	and a Parser that processes the
tokens according to a grammar and build the command table.

*/

static int	def_quot_state(char *line, int *i_ptr, t_token *toklist)
{
	char	c;
	char	next_c;
	int i;

	i = *i_ptr;
	c = line[i];
	next_c = line[i + 1];
	// state 1: we are not currently inside quotes (QUOTE_NORMAL)
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
		else if (c == '"')
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
	// state 2: we are currently inside double quotes (QUOTE_DOUBLE)
	else if (toklist->quote == QUOTE_DOUBLE)
	{
		// if found collect till the next one; set a flag
		// on unmatched quotes return error, and free
	}
	// state 3: we are currently inside single quotes (QUOTE_SINGLE)
	else if (toklist->quote == QUOTE_SINGLE)
	{
	}
	*i_ptr = i;
	return (EXIT_SUCCESS);
}

// Lexer allocates every t_token node and each content string.
// return head of list if success or NULL in case of error
t_token	*tokenizer(const char *line)
{
	int i;
	t_token *toklist;
	t_token_list *token_head;

	i = 0;
	token_head = NULL;
	// toklist->quote = QUOTE_NORMAL;
	while (line[i])
	{
		// a funct that advances i for each iter and checks for whitespaces
		i = skip_whitespace(line, i);
		// check if we hit the null term after skipping spaces
		if (line[i] == '\0') 
			break ;
		toklist = (t_token *)ft_calloc(1, sizeof(t_token));
		if (!toklist)
			return (NULL);
		// defoult state of quote
		toklist->quote = QUOTE_NORMAL;
		// token definition function
		def_quot_state((char *)line, &i, toklist);
		if (toklist->typ == TOKEN_WORD)
			// iterate i till it hits a space or pipe quote
			// and allocate toklist->content
			i = collect_word_content(line, i, toklist);
		else if (toklist->quote != QUOTE_NORMAL)
			i = collect_word_content(line, i, toklist);
		// add_token_to_list(&head, toklist);
		// storing the token found in the list
	}
	return (token_head);
}
