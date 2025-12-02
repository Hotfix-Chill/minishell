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
puts the characters together into words called tokens, and a Parser that processes the 
tokens according to a grammar and build the command table.

*/

int tokenizer(char *line)
{
	int i;
	char c;
	t_state state;
	t_token *toklist;

	i = 0;
	state = STATE_NORMAL;
	while (line[i])
	{
		c = line[i];
		if (state == STATE_NORMAL)
		{
			if (c == '\'')
				state = STATE_SINGLE_QUOTE;
			else if (c == '"')
				state = STATE_DOUBLE_QUOTE;	
		}
		i++;
	}
}