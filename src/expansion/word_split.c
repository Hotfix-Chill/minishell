/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:11:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 14:36:27 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_from_args(t_cmds *cmd, char **argv, bool *no_expand,
		bool *no_split)
{
	size_t	i;
	size_t	idx;

	i = 0;
	idx = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->no_split && cmd->no_split[i])
		{
			if (append_quoted_word(cmd, i, argv, no_expand, no_split,
					&idx) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else if (fill_split_words(cmd->argv[i], argv, no_expand, no_split,
				&idx) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	rebuild_argv(t_cmds *cmd)
{
	char	**new_argv;
	bool	*new_no_expand;
	bool	*new_no_split;
	size_t	total_words;

	total_words = count_total_words(cmd);
	if (alloc_arrays(total_words, &new_argv, &new_no_expand,
			&new_no_split) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (build_from_args(cmd, new_argv, new_no_expand,
			new_no_split) != EXIT_SUCCESS)
		return (free_split_arrays(new_argv, new_no_expand, new_no_split));
	free_split(cmd->argv);
	free(cmd->no_expand);
	free(cmd->no_split);
	cmd->argv = new_argv;
	cmd->no_expand = new_no_expand;
	cmd->no_split = new_no_split;
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
