/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:54:26 by abita             #+#    #+#             */
/*   Updated: 2026/01/24 15:05:01 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*init_cmd_list(void)
{
	t_stack	*lst;

	lst = (t_stack *)ft_calloc(1, sizeof(t_stack));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst);
}

t_cmds	*create_cmds(void)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->no_split = NULL;
	cmd->builtin = false;
	cmd->next = NULL;
	return (cmd);
}

int	add_cmd_to_list(t_stack *lst, t_cmds *cmd)
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
