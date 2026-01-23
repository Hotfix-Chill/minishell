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

static int	handle_pipe(t_token **tok_ptr, t_cmds **curr_cmd_ptr, \
	t_stack *cmd_list)
{
	t_token		*tok;
	t_cmds		*curr_cmd;

	*tok = *tok_ptr;
	*curr_cmd = *curr_cmd_ptr;
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

static int	parser_loop(t_token *tok, t_cmds **curr_cmd, \
	t_stack *cmd_list, t_data *data)
{
	while (tok)
	{
		if (handle_pipe(&tok, curr_cmd, cmd_list) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		else if (tok->typ == TOKEN_REDIR)
		{
			if (!tok->next || tok->next->typ != TOKEN_WORD)
				return (EXIT_FAILURE);
			if (add_redir_to_cmd(*curr_cmd, tok, tok->next, data) \
				!= EXIT_SUCCESS)
				return (EXIT_FAILURE);
			tok = tok->next->next;
		}
		else if (tok->typ == TOKEN_WORD)
		{
			if (add_arg_to_cmd(*curr_cmd, tok->content, tok->no_expand) \
				!= EXIT_SUCCESS)
				return (EXIT_FAILURE);
			tok = tok->next;
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	check_builtins(t_stack *lst)
{
	t_cmds	*cmd;

	if (!lst)
		return ;
	cmd = lst->head;
	while (cmd)
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			cmd->builtin = false;
			cmd = cmd->next;
			continue ;
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
}

t_stack	*parsing(t_token_list *token, t_data *data)
{
	t_cmds	*curr_cmd;
	t_stack	*cmd_list;

	cmd_list = init_cmd_list();
	if (!cmd_list)
		return (NULL);
	curr_cmd = create_cmds();
	if (!curr_cmd)
		return (free(cmd_list), NULL);
	if (parser_loop(token->head, &curr_cmd, cmd_list, data) != EXIT_SUCCESS)
		return (free_cmds(curr_cmd), free_cmd_list(cmd_list), NULL);
	if ((!curr_cmd->argv && !curr_cmd->redirs))
		return (free_cmds(curr_cmd), free_cmd_list(cmd_list), NULL);
	if (add_cmd_to_list(cmd_list, curr_cmd) != EXIT_SUCCESS)
		return (free_cmd_list(cmd_list), NULL);
	check_builtins(cmd_list);
	return (cmd_list);
}
