/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:21:56 by abita             #+#    #+#             */
/*   Updated: 2026/01/14 14:27:58 by abita            ###   ########.fr       */
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

char 	*extract_env(t_data *data, char *new_var)
{
	int	j;

	j = 0;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], new_var, ft_strlen(new_var)) == 0
			&& data->env[j][ft_strlen(new_var)] == '=')
			return (ft_strchr(data->env[j], '=') + 1);
		j++;
	}
	return (NULL);
}

char	*extract_var(const char *args, int start)
{
	int i;

	i = 0;
	while (ft_isalnum(args[start + i + 1]) || args[start + i + 1] == '_')
	i++;
	return (ft_substr(args, start + 1, i));
}

char	*expan_str(const char *args, t_data *data)
{
	int		i;
	char	*new_var;
	char	*env_var;
	char	*result;
	
	if (!args || !data)
		return (ft_strdup(""));
	i = 0;
	while (args[i])
	{
		if (args[i] == '$')
		{
			if (args[i + 1] == '?')
				return (ft_itoa(data->return_value));

			new_var = extract_var(args, i);
			printf("new_var: %s\n", new_var);
		
			env_var = extract_env(data, new_var);
			printf("env_var: %s\n", env_var);
		
			if (env_var)
				result = ft_strdup(env_var);
			else
				result = ft_strdup("");
			free(new_var);
			return (result);
			printf("new_var_final: %s\n", result);
		}
		i++;
	}
	return (ft_strdup(args));
}

int	expansion(t_stack *cmd_list, t_data *data)
{
	int		i;
	char	*expanded;
	t_cmds	*cmd;

	if (!cmd_list || !data)
		return (EXIT_FAILURE);
	i = 0;
	cmd = cmd_list->head;
	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("Processing command with argv[%d] = %s\n", i, cmd->argv[i]);
			expanded = expan_str(cmd->argv[i], data); // check if failure
			if (!expanded)
				return (EXIT_FAILURE);
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
			i++;
		}
		// here to expand redirections
		while (cmd->redirs)
		{
			expanded = expan_str(cmd->redirs->filename, data);
			// check if failure
			free(cmd->redirs->filename);
			cmd->redirs->filename = expanded;
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
