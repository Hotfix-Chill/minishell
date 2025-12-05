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

static int append_char_to_content(t_token *toklist, char c)
{
	char *new_content;
	char *old_content;
	char char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';

	old_content = toklist->content;
	new_content = ft_strjoin(old_content, char_str); // if not null join the existing str
	if (!new_content)
		return (-1); // ALLOCATION_FAILED create an enum to clean up
	if (toklist->content) // here i free the old contetn and update the pointer
		free(toklist->content);
	toklist->content = new_content;
	return (EXIT_SUCCESS);
}

static int collect_quote_content(char *line, int *i_ptr, t_token *toklist)
{
	int prev_quote;
	char c;
	int i;

	i = *i_ptr;
	while (line[i])
	{

		// check if we hit a boundary (space, pipe, redir, eof)
		c = line[i];
		if (toklist->quote == QUOTE_NORMAL)
		{
			if ((ft_isspace(c) || c == '|' || c == '<' || c == '>'))
				break ; // stop collecting if outside the quotes
		}
		// check if we hit a quote that changes the state (i.e. closes the quote)
		// cases like ('word'abc), it must also be checked if it ends the quote
		prev_quote = toklist->quote;
		def_quote_state(line, &i, toklist);
		if (prev_quote != toklist->quote)
		{
			if (toklist->quote == QUOTE_NORMAL)
				break ;
			continue ; // state was changed, returned error or new quote and brake cus i now is incremented to the next
		}
		if (append_char_to_content(toklist, line[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	*i_ptr = i;
	return (EXIT_SUCCESS);
}


static int	def_quot_state(char *line, int *i_ptr, t_token *toklist)
{
	char	c;
	char	next_c;
	int i;

	i = *i_ptr;
	c = line[i];
	next_c = line[i + 1];
	// state 1: we are not currently inside quotes (QUOTE_NORMAL)
	normal_quote_state(c, next_c, i, toklist);

	// state 2: we are currently inside double quotes (QUOTE_DOUBLE)
	// double_quote_state(c, i, toklist);
	if (toklist->quote == QUOTE_DOUBLE)
	{
		// if found collect till the next one; set a flag
		// on unmatched quotes return error, and free
		
		// found the closing quote
		if (c == '"')
		{
			toklist->quote = QUOTE_NORMAL;
			i++;
		}
		else if (c )

	}

	// state 3: we are currently inside single quotes (QUOTE_SINGLE)
	// single_quote_state(c, i, toklist);
	else if (toklist->quote == QUOTE_SINGLE)
	{
		// found the closing quote
		if (c == '\'')
		{
			toklist->quote = QUOTE_NORMAL;
			i++;
		}
		else
		{

		}
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
			i = collect_word_content(line, &i, toklist);
		else if (toklist->quote != QUOTE_NORMAL)
			i = collect_word_content(line, i, toklist);
		// add_token_to_list(&head, toklist);
		// storing the token found in the list
	}
	return (token_head);
}
