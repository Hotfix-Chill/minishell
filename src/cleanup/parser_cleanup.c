/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:39:26 by abita             #+#    #+#             */
/*   Updated: 2026/01/23 16:22:41 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_arg(char **argv)
{
	int i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

static void	free_redirs(t_redirs *r)
{
	t_redirs	*next;

	while (r)
	{
		next = r->next;
		free(r->filename);
		free(r);
		r = next;
	}
}
void	free_cmds(t_cmds *cmd)
{
	if (!cmd)
		return ;
	free_arg(cmd->argv);
	free_redirs(cmd->redirs);
	if (cmd->no_expand != NULL)
	{
		free(cmd->no_expand);
		cmd->no_expand = NULL;
	}
	if (cmd->no_split != NULL)
	{
		free(cmd->no_split);
		cmd->no_split = NULL;
	}
	if (cmd)
		free(cmd);
}

void	free_cmd_list(t_stack *lst)
{
	t_cmds	*cur;
	t_cmds	*next;

	if (!lst)
		return ;
	cur = lst->head;
	while (cur)
	{
		next = cur->next;
		free_cmds(cur);
		cur = next;
	}
	free(lst);
}
