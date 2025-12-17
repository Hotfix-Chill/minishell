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
	t_token			*tok;
	t_cmds			*curr_cmd;
	t_stack			*cmd_list;

	cmd_list = init_cmd_list(); /// (holds all items)
	if (!cmd_list)
		return (NULL);
	curr_cmd = create_cmds(); // (current command) item im currently putting in 
	if (!curr_cmd)
		return (NULL);
	tok = token->head; /// moving through the token list to each token
	while (tok)
	{
		
		if (tok->typ == TOKEN_PIPE)
		{
			// so i detect what the current cmd is, 
			// so in this case pipe i set the flag as true 
			// and add it to the list.
			curr_cmd->pipe_after = true;
			if (add_cmd_to_list(cmd_list, curr_cmd) != EXIT_SUCCESS)
				return (NULL);
			// here start a new cmd
			curr_cmd = create_cmd();
		}
		else if(tok->typ == TOKEN_REDIR)
		{
			// add c to the redir list
			add_redir_to_cmd(curr_cmd, tok, tok->next);
			tok = tok->next; // skip the next token as its filename
		}
		else if (tok->typ == TOKEN_WORD)
			add_arg_to_cmd(curr_cmd, tok->content);
		/*
		Example:
		Token: "echo"
		Before: current_cmd->argv = NULL
		After:  current_cmd->argv = ["echo", NULL]

		Token: "hello"
		Before: current_cmd->argv = ["echo", NULL]
		After:  current_cmd->argv = ["echo", "hello", NULL]
		
		*/
		
		tok = tok->next;
	}
	add_cmd_to_list(cmd_list, curr_cmd);
	return (cmd_list);
}
