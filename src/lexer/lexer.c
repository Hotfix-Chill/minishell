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
static int	decide_token_type(char *line, int *i_ptr, t_token *tok)
{
	int		i;
	int		res;

	i = *i_ptr;
	res = redir_check(line, i_ptr, tok);
	if (res == REDIR_ERROR)
		return (-1);
	else if (res == REDIR_FOUND)
		return (EXIT_SUCCESS);
	else if (line[i] == '|')
		return (tok->typ = TOKEN_PIPE, *i_ptr = i + 1, EXIT_SUCCESS);
	else if (line[i] == '>')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_OUT, *i_ptr = i + 1,
			EXIT_SUCCESS);
	else if (line[i] == '<')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_IN, *i_ptr = i + 1,
			EXIT_SUCCESS);
	tok->typ = TOKEN_WORD;
	tok->quote = QUOTE_NORMAL;
	return (EXIT_SUCCESS);
}
/*
	tokens contetnt setup this for non word tokens
*/
static int set_operator_content(t_token *tok)
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
// main tokenizer
// Lexer allocates every t_token node and each content string.
// return head of list if success or NULL in case of error
t_token_list	*tokenizer(const char *line)
{
	int				i;
	t_token			*tok;
	t_token_list	*lst;

	i = 0;
	lst = init_token_list();
	if (!lst)
		return (NULL);
	// toklist->quote = QUOTE_NORMAL;
	while (line && line[i])
	{
		// a funct that advances i for each iter and checks for whitespaces
		i = skip_whitespace((char *)line, i);
		// check if we hit the null term after skipping spaces
		if (!line[i])
			break ;
		tok = create_token();
		if (!tok)
			return (cleanup_all(lst, NULL));
		// token definition function
		decide_token_type((char *)line, &i, tok);
		if (tok->typ == TOKEN_WORD)
		{
			if (collect_word_content((char *)line, &i, tok) != EXIT_SUCCESS)
				return (cleanup_all(lst, tok));
		}
		else
		{
			if (set_operator_content(tok) != EXIT_SUCCESS)
				return (cleanup_all(lst, tok));

		}
		// here i add to the list
		if (add_token(lst, tok) != EXIT_SUCCESS)
			return (cleanup_all(lst, tok));
	}
	return (lst);
}
