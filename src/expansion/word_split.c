/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:11:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 19:24:38 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 7) Populate the new argv by splitting unquoted entries and copying quoted. */
static int	build_from_args(t_cmds *cmd, t_buffer *buf)
{
	size_t	i;
	size_t	idx;

	i = 0;
	idx = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->no_split && cmd->no_split[i])
		{
			if (append_quoted_word(cmd, i, buf) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else if (fill_split_words(cmd->argv[i], buf) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	rebuild_argv(t_cmds *cmd)
{
	t_buffer	buf;

	buf.idx	= 0;
	if (alloc_arrays(count_total_words(cmd), &buf) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (build_from_args(cmd, &buf) != EXIT_SUCCESS)
		return (free_split_arrays(&buf));
	cmd->argv = buf.argv;
	cmd->no_expand = buf.no_expand;
	cmd->no_split = buf.no_split;
	return (EXIT_SUCCESS);
}

void	word_splitting(t_stack *cmd_list, t_data *data)
{
	t_cmds	*cmd;

	if (!cmd_list)
		return ;
	cmd = cmd_list->head;
	while (cmd)
	{
		if (rebuild_argv(cmd) != EXIT_SUCCESS)
			cleanup(data, ERROR);
		cmd = cmd->next;
	}
}
