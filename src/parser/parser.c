/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:52 by abita             #+#    #+#             */
/*   Updated: 2025/12/16 15:41:54 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
	The name of the command Bash has to execute is always 
	the first word in the line. The rest of the command data is split 
	into words which make the arguments.	
*/
/////////////////////////////////
/*
	P​arser that processes the tokens according to a grammar 
	and build the command table.
*/

t_stack *parsing(char *token)
{
	int i;
	t_token			*t_tok;
	char c;
	char next_c;

	i = 0;
	while (token[i])
	{
		c = token[i];
		next_c = token[i+1];
		if (token[1] && t_tok->content == TOKEN_WORD)
		{
			// add c to the arg list

		}
		else if(t_tok->content == TOKEN_REDIR)
		{
			// add c to the redir list

		}
		else if (t_tok->content == TOKEN_PIPE)
		{
			// add c to the pipe list
		}	
		i++;
	}
	return (token);
}