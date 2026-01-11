/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:52 by abita             #+#    #+#             */
/*   Updated: 2026/01/11 15:18:59 by abita            ###   ########.fr       */
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

		/*
		Example:
		Token: "echo"
		Before: current_cmd->argv = NULL
		After:  current_cmd->argv = ["echo", NULL]

		Token: "hello"
		Before: current_cmd->argv = ["echo", NULL]
		After:  current_cmd->argv = ["echo", "<<", "file name", NULL]
*/

static int handle_pipe(t_token **tok_ptr, t_cmds **curr_cmd_ptr, t_stack *cmd_list)
{
	t_token *tok = *tok_ptr;
	t_cmds *curr_cmd = *curr_cmd_ptr;

	if (tok->typ == TOKEN_PIPE)
	{
		if (!curr_cmd->argv && !curr_cmd->redirs)
			return (EXIT_FAILURE);
		if (add_cmd_to_list(cmd_list, curr_cmd) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		curr_cmd = create_cmds();
		if (!curr_cmd)
			return (EXIT_FAILURE);
		*curr_cmd_ptr = curr_cmd;
		*tok_ptr = tok->next;
	}
	return (EXIT_SUCCESS);
}

static int parser_loop(t_token *tok, t_cmds **curr_cmd, t_stack *cmd_list)
{
	while (tok)		//loops through all tokens and processes them based on their type
	{
		if (handle_pipe(&tok, curr_cmd, cmd_list) != EXIT_SUCCESS) // PIPE TOKE
			return (EXIT_FAILURE);
		else if(tok->typ == TOKEN_REDIR) // REDIR_TOKEN
		{
			if (!tok->next || tok->next->typ != TOKEN_WORD)
				return (EXIT_FAILURE);
			if (add_redir_to_cmd(*curr_cmd, tok, tok->next) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			tok = tok->next->next;
		}
		else if (tok->typ == TOKEN_WORD) // WORD_TOKEN
		{
			if (add_arg_to_cmd(*curr_cmd, tok->content) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			tok = tok->next;
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
static bool check_builtins(t_stack *lst)
{
	t_cmds *cmd;

	if (!lst)
		return (false);
	cmd = lst->head;
	while (cmd)
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			cmd->builtin = false;
			cmd = cmd->next;
			continue;
		}
		if (ft_strcmp(cmd->argv[0], "echo") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "cd") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "export") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "unset") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "env") == 0)
			cmd->builtin = true;
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			cmd->builtin = true;
		else
			cmd->builtin = false;
		cmd = cmd->next;
	}
	return (true);
}

// taking the tooken list from the header
t_stack *parsing(t_token_list *token)
{
	t_cmds			*curr_cmd;
	t_stack			*cmd_list;

	cmd_list = init_cmd_list(); // allocates t_stack
	if (!cmd_list)
		return (NULL);
	curr_cmd = create_cmds();		// allocates t_cmds
	if (!curr_cmd)
		return (free(cmd_list), NULL);
	if (parser_loop(token->head, &curr_cmd, cmd_list) != EXIT_SUCCESS)
		return (free_cmds(curr_cmd), free_cmd_list(cmd_list), NULL);
	if ((!curr_cmd->argv && !curr_cmd->redirs))
			return (free_cmd_list(cmd_list), NULL);
	if (add_cmd_to_list(cmd_list, curr_cmd) != EXIT_SUCCESS)
		return (free_cmd_list(cmd_list), NULL);
	if (!check_builtins(cmd_list))
		return (free_cmd_list(cmd_list), NULL);
	return (cmd_list);
}
