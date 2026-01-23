/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:11:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/23 12:30:23 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_ifs_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t	count_words(const char *str)
{
	size_t	count;
	size_t	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_ifs_char(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i] && !is_ifs_char(str[i]))
			i++;
	}
	return (count);
}

static int	fill_split_words(const char *str, char **argv, bool *no_expand,
		bool *no_split, size_t *idx)
{
	size_t	i;
	size_t	start;
	char	*word;
	i = 0;
	while (str && str[i])
	{
		while (str[i] && is_ifs_char(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_ifs_char(str[i]))
			i++;
		word = ft_substr(str, start, i - start);
		if (!word)
			return (EXIT_FAILURE);
		argv[*idx] = word;
		no_expand[*idx] = false;
		no_split[*idx] = false;
		(*idx)++;
	}
	return (EXIT_SUCCESS);
}

static size_t	count_total_words(t_cmds *cmd)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->no_split && cmd->no_split[i])
			total++;
		else
			total += count_words(cmd->argv[i]);
		i++;
	}
	return (total);
}

static int	alloc_arrays(size_t total, char ***argv, bool **no_expand,
		bool **no_split)
{
	*argv = ft_calloc(total + 1, sizeof(char *));
	*no_expand = ft_calloc(total + 1, sizeof(bool));
	*no_split = ft_calloc(total + 1, sizeof(bool));
	if (!*argv || !*no_expand || !*no_split)
		return (free(*argv), free(*no_expand), free(*no_split), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	free_split_arrays(char **argv, bool *no_expand, bool *no_split)
{
	free_split(argv);
	free(no_expand);
	free(no_split);
	return (EXIT_FAILURE);
}

static int	append_quoted_word(t_cmds *cmd, size_t i, char **argv,
		bool *no_expand, bool *no_split, size_t *idx)
{
	argv[*idx] = ft_strdup(cmd->argv[i]);
	if (!argv[*idx])
		return (EXIT_FAILURE);
	no_expand[*idx] = false;
	no_split[*idx] = true;
	(*idx)++;
	return (EXIT_SUCCESS);
}

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

	if (alloc_arrays(count_total_words(cmd), &new_argv, &new_no_expand,
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

void	word_splitting(t_stack *cmd_list)
{
	t_cmds	*cmd;

	if (!cmd_list)
		return ;
	cmd = cmd_list->head;
	while (cmd)
	{
		if (rebuild_argv(cmd) != EXIT_SUCCESS)
			return ;
		cmd = cmd->next;
	}
}
