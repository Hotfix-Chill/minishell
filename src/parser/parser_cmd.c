/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:37:55 by abita             #+#    #+#             */
/*   Updated: 2025/12/17 17:37:56 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack *init_cmd_list(void)
{
	t_stack *lst;

	lst = (t_stack *)ft_calloc(1, sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst); 
}

t_cmds *create_cmds(void)
{
	t_cmds *cmd;

	cmd = (t_cmds *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->pipe_after = false;
	cmd->next = NULL;
	return (cmd);
}

int add_cmd_to_list(t_stack *lst, t_cmds *node)
{
	if (!lst || !node)
		return (-1);
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	lst->size++;
	return (EXIT_SUCCESS);
}
int count_args(char **args)
{
	int count;

	count = 0;
	if (!args)
		return (NULL);
	while (args[count])
		count++;
	return (count);
}

// Add an argument to command's argv array
int add_arg_to_cmd(t_cmds *cmd, const char *arg)
{
	
}