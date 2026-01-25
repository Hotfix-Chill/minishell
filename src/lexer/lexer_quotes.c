/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:43:33 by abita             #+#    #+#             */
/*   Updated: 2026/01/25 19:12:22 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote_char(t_token *tok, char c)
{
	if (tok->quote == QUOTE_NORMAL)
	{
		if (c == '\'')
		{
			tok->quote = QUOTE_SINGLE;
			tok->quoted = true;
			return (1);
		}
		if (c == '\"')
		{
			tok->quote = QUOTE_DOUBLE;
			return (1);
		}
	}
	else if (is_closing_quote(c, tok->quote))
	{
		tok->quote = QUOTE_NORMAL;
		tok->quoted = true;
		return (1);
	}
	return (EXIT_SUCCESS);
}
