/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:43:33 by abita             #+#    #+#             */
/*   Updated: 2026/01/24 15:06:02 by abita            ###   ########.fr       */
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
			tok->no_expand = true;
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
