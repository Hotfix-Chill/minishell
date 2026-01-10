/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:26:29 by abita             #+#    #+#             */
/*   Updated: 2025/12/09 17:03:26 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

// Returns true if this character closes the current quote state
bool is_closing_quote(char c, t_quote_type quote)
{
	bool result;

	result = false;
	if (quote == QUOTE_SINGLE && c == '\'')
		result = true;
	else if (quote == QUOTE_DOUBLE && c == '\"')
		result = true;
	else
		result = false;
	return (result);
}

// Returns true if we should stop collecting this word
bool should_break_word(char c, t_quote_type quote)
{
	if (quote != QUOTE_NORMAL)
		return (false); // inside quotes nothing breaks the word
	return (is_metachar(c) || ft_isspace(c));
}
