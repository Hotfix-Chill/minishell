/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:37:55 by abita             #+#    #+#             */
/*   Updated: 2026/01/11 08:06:42 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack *init_cmd_list(void)
{
	t_stack *lst;

	lst = (t_stack *)ft_calloc(1, sizeof(t_stack));
	if (!lst)
		return (NULL);
	// lst->head = NULL;
	// lst->tail = NULL;
	// lst->size = 0;
	return (lst);
}

t_cmds *create_cmds(void)
{
	t_cmds *cmd;

	cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	// cmd->argv = NULL;
	// cmd->redirs = NULL;
	// cmd->builtin = false;
	// cmd->next = NULL;
	return (cmd);
}

int add_cmd_to_list(t_stack *lst, t_cmds *cmd)
{
	if (!lst || !cmd)
		return (-1);
	if (!lst->head)
	{
		lst->head = cmd;
		lst->tail = cmd;
	}
	else
	{
		lst->tail->next = cmd;
		lst->tail = cmd;
	}
	lst->size++;
	return (EXIT_SUCCESS);
}
static int count(t_cmds *curr_cmd)
{
	int arg_count;

	arg_count = 0;
	if (curr_cmd->argv != NULL)
	{
		while (curr_cmd->argv[arg_count])
			arg_count++;
	}
	return (arg_count);
}
// Add the token content like words to command's argv array
int add_arg_to_cmd(t_cmds *curr_cmd, const char *tok_content)
{
	int arg_count;
	int i;
	char **new_argv;

	if (!curr_cmd || !tok_content)
		return (-1);
	arg_count = count(curr_cmd);
	new_argv = (char **)ft_calloc(arg_count + 2, sizeof(char *));
	if (!new_argv)
		return (-1);
	i = 0;
	while (i < arg_count)
	{
		new_argv[i] = curr_cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(tok_content);
	if (!new_argv[i])
		return (free(new_argv), -1);
	i++;
	new_argv[i] = NULL;
	free(curr_cmd->argv);
	curr_cmd->argv = new_argv;
	return (EXIT_SUCCESS);
}
