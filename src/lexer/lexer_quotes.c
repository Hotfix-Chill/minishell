/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:43:33 by abita             #+#    #+#             */
/*   Updated: 2026/01/11 15:20:24 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	QUOTE STATE - The heart of the lexer ^^
*/

// Handles quote translations, returns 1 if quote was consumed, 0 if its content
int handle_quote_char(t_token *tok, char c)
{
	// opening quote form the normal state
	if (tok->quote == QUOTE_NORMAL)
	{
		if (c == '\'')
		{
			tok->quote = QUOTE_SINGLE;
			return (1); // consume the quote. dont add to content
		}
		if (c == '\"')
		{
			tok->quote = QUOTE_DOUBLE;
			return (1);
		}
	}
	// Closing quote 
	else if (is_closing_quote(c, tok->quote))
	{
		tok->quote = QUOTE_NORMAL;
		return (1); // consume closing quote
	}
	// inside quotes but not the closing quote, its a literal content
	return (EXIT_SUCCESS);
}
