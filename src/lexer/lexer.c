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

static int token_check(const char *line, int *i, t_token *tok)
{
	if(decide_token_type((char *)line, i, tok) != EXIT_SUCCESS)
	{
		printf("syntax error\n");
		return (EXIT_FAILURE);
	}
	if (tok->typ == TOKEN_WORD)
	{
		if (collect_word_content((char *)line, i, tok) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (set_operator_content(tok) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
static int lexer_loop(const char *line, t_token_list *lst, t_token	*tok)
{
	int				i;

	i = 0;
	while (line && line[i])
	{
		// a funct that advances i for each iter and checks for whitespaces
		i = skip_whitespace((char *)line, i);
		// check if we hit the null term after skipping spaces
		if (!line[i])
			break ;
		tok = create_token();
		if (!tok)
			return (cleanup_all(lst, NULL), EXIT_FAILURE);
		if (token_check(line, &i, tok) != EXIT_SUCCESS)
			return (cleanup_all(lst, tok), EXIT_FAILURE);
		if (add_token(lst, tok) != EXIT_SUCCESS)
			return (cleanup_all(lst, tok), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// main tokenizer
// Lexer allocates every t_token node and each content string.
// return head of list if success or NULL in case of error
t_token_list	*tokenizer(const char *line)
{
	t_token_list	*lst;
	t_token			*tok;

	tok = NULL;
	lst = init_token_list();
	if (!lst)
		return (NULL);
	// toklist->quote = QUOTE_NORMAL;
	if (lexer_loop(line, lst, tok) == EXIT_SUCCESS)
		return (lst);
	//cleanup_token(tok);
	return NULL;
}
