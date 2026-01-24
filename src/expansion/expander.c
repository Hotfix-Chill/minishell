/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:21:56 by abita             #+#    #+#             */
/*   Updated: 2026/01/24 20:04:09 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_and_join(t_data *data, char *str, size_t idx)
{
	char	*expand_str;
	char	*sub_str;
	char	*final;
	char	*line;

	final = NULL;
	sub_str = NULL;
	expand_str = ft_calloc(idx + 1, sizeof(char));
	if (!expand_str)
		return (NULL);
	ft_strncpy(expand_str, str, idx + 1);
	if (idx + 1 <= ft_strlen(str))
	{
		sub_str = ft_substr(str, idx, ft_strlen(&str[idx]));
		if (!sub_str)
			return (free(expand_str), NULL);
	}
	help_expand_lookup(data, expand_str, &final);
	free(expand_str);
	line = partial_expansion(final, sub_str);
	if (line)
		return (line);
	line = ft_strjoin(final, sub_str);
	return (free(final), free(sub_str), line);
}

char	*extract_var(t_data *data, char *extract_var)
{
	size_t	idx;
	char	*value;

	if (!extract_var)
		return (NULL);
	idx = validifier_var(extract_var);
	value = expand_and_join(data, extract_var, idx);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static int	expand_cmd(t_data *data, t_cmds *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (!cmd->no_expand[i] && find_char(cmd->argv[i], '$') != NO_DOLLAR)
		{
			expanded = split_dollar(data, cmd->argv[i]);
			if (!expanded)
				return (EXIT_FAILURE);
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
		}
		i++;
	}
	return (0);
}

static int	expand_redirs(t_data *data, t_cmds *cmd)
{
	t_redirs	*redirs;
	char		*expanded;

	redirs = cmd->redirs;
	while (redirs)
	{
		if (!redirs->no_expand && find_char(redirs->filename, '$') != NO_DOLLAR)
		{
			expanded = split_dollar(data, redirs->filename);
			if (!expanded)
				return (EXIT_FAILURE);
			free(redirs->filename);
			redirs->filename = expanded;
		}
		redirs = redirs->next;
	}
	return (0);
}

void	expansion(t_stack *cmd_list, t_data *data)
{
	t_cmds	*cmd;

	if (VERBOSE)
		printf("INSIDE EXPANSION CMD\n");
	cmd = cmd_list->head;
	if (!cmd_list || !data)
		cleanup(data, ERROR);
	while (cmd)
	{
		if (expand_cmd(data, cmd) == EXIT_FAILURE
			|| expand_redirs(data, cmd) == EXIT_FAILURE)
			break ;
		cmd = cmd->next;
	}
}
