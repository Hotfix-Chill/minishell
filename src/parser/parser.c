/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:52 by abita             #+#    #+#             */
/*   Updated: 2025/12/17 17:38:20 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
	P​arser that processes the tokens according to a grammar 
	and build the command table.

	Parser's Job:

	1. Group tokens into commands (split by pipes)
	2. Separate arguments from redirections
	3. Build t_cmds nodes
	4. Link them in a list


	Implement init_cmd_list(), create_cmd(), free_cmd_list()
*/



// taking the tooken list from the header
t_stack *parsing(t_token_list *token)
{
	t_token			*cur;

	cur = token->head;
	while (cur)
	{
		
		if (cur->typ == TOKEN_WORD)
		{
			// add c to the arg list

		}
		else if(cur->typ == TOKEN_REDIR)
		{
			// add c to the redir list

		}
		else if (cur->typ == TOKEN_PIPE)
		{
			// add c to the pipe list
		}
		cur = cur->next;
		cur++;
	}
	return (token);
}
