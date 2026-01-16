/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:21:56 by abita             #+#    #+#             */
/*   Updated: 2026/01/16 08:51:09 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Shell Parameter Expansion
		The ‘$’ character introduces parameter expansion, command substitution,
	or arithmetic expansion. The parameter name or symbol to be expanded may be
	enclosed in braces, which are optional but serve to protect the variable
	to be expanded from characters immediately following it which could be
	interpreted as part of the name.
*/

#include "minishell.h"

char 	*extract_var(t_data *data, char *extract_var)
{
	size_t	i;


	i = 0;
	while (i < data->export_len)
	{
		if (ft_strcmp(data->export[i].key, extract_var) == 0)
			return (data->export[i].value);
		i++;
	}
	return (NULL);
}

static int	expand_cmd(t_data  *data, t_cmds *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (find_char(cmd->argv[i], '$') == NOT_FOUND_DOLLAR)
		{
			i++;
			continue;
		}
		expanded = split_dollar(data, cmd->argv[i]);
		if (!expanded)
			return (EXIT_FAILURE);
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		printf("EXPANDED CMD STRING: %s\n", expanded);
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
		if (find_char(redirs->filename, '$') == NOT_FOUND_DOLLAR)
		{
			redirs = redirs->next;
			continue;
		}
		expanded = split_dollar(data,redirs->filename);
		if (!expanded)
			return (EXIT_FAILURE);
		free(redirs->filename);
		redirs->filename = expanded;
		redirs = redirs->next;
	}
	return (0);
}

int	expansion(t_stack *cmd_list, t_data *data)
{
	t_cmds	*cmd;

	cmd = cmd_list->head;
	if (!cmd_list || !data)
		return (EXIT_FAILURE);
	while (cmd)
	{
		if (expand_cmd(data, cmd) == EXIT_FAILURE
			|| expand_redirs(data, cmd) == EXIT_FAILURE)
			cleanup(data, ERROR);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
