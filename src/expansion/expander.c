/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:21:56 by abita             #+#    #+#             */
/*   Updated: 2026/01/16 15:50:06 by pjelinek         ###   ########.fr       */
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

int	validifier_var(t_data *data, char *str)
{
	size_t	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		data->flag.not_valid = true;
		return (1);
	}
	i = 1;
	while (str[i] && str[i] !=  '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '$')
		{
			data->flag.not_valid = true;
			return (i);
		}
		i++;
	}
	return (i);
}

/* char	*expand_and_join(t_data *data, char *str, int nb)
{

	return ;
} */

char 	*extract_var(t_data *data, char *extract_var)
{
	size_t	i;

	/*size_t idx = validifier_var(data, extract_var);
	if (!!data->flag.not_valid)
		return (expand_and_join(data, extract_var, idx)); */

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
		if (find_char(cmd->argv[i], '$') != NOT_FOUND_DOLLAR)
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
		if (find_char(redirs->filename, '$') != NOT_FOUND_DOLLAR)
		{
			expanded = split_dollar(data,redirs->filename);
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


	cmd = cmd_list->head;
	//printf("ARGV[1]: %s\n", cmd->argv[1]);
	if (!cmd_list || !data)
		cleanup(data, ERROR);
	while (cmd)
	{
		if (expand_cmd(data, cmd) == EXIT_FAILURE
			|| expand_redirs(data, cmd) == EXIT_FAILURE)
			cleanup(data, ERROR);
		cmd = cmd->next;
	}
}
