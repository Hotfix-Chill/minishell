/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:39:26 by abita             #+#    #+#             */
/*   Updated: 2026/01/11 08:04:06 by pjelinek         ###   ########.fr       */
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

static void free_redirs(t_redirs *r)
{
	t_redirs *next;

	while (r)
	{
		next = r->next;
		free(r->filename);
		free(r);
		r = next;
	}
}

void free_cmd_list(t_stack *lst)
{
	t_cmds *cur;
	t_cmds *next;

	if (!lst)
		return ;
	cur = lst->head;
	while (cur)
	{
		next = cur->next;
		free_arg(cur->argv);
		free_redirs(cur->redirs);
		free(cur);
		cur = next;
	}
	free(lst);
}
