/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:21:56 by abita             #+#    #+#             */
/*   Updated: 2026/01/08 14:21:57 by abita            ###   ########.fr       */
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


char **expan_str(const char *str, t_data *data)
{
	int i;
	char *result;

	// to check if it needs expansion
	if (!has_variable(str))
		return (ft_strdup(str)); // if there are no variables then just copy ..
	result = ft_strdup(""); //.. start w empty str
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			//so literaly here i find a variable, just extract the var, 
			//check it and then add the value to the result
		}
		else
		{
			append_char(&result, str[i]);
			i++;
		}
	}
	return (result);
}

int expansion(t_stack *cmd_list, t_data *data)
{
	int i;
	char **expanded;
	t_cmds *cmd;

	if (!cmd_list || !data)
		return (EXIT_FAILURE);
	i = 0;
	cmd = cmd_list->head;
	while (cmd)
	{
		i = 0;
		// here to expand argv
		while (cmd->argv[i])
		{
			printf("Processing command with argv[%d] = %s\n", i, cmd->argv[i]);
			// look now at each argv[0], [1], for variables.. so if i have $USER
			// SO CHAR BY CHAR I CHECK ifff i see a $ sign i extract the variable
			expanded = expan_str(cmd->argv[i], data); // check if failure
			free(cmd->argv[i]);
			cmd->argv[i] = expanded;
			i++;
		}
		// here to expand redirections
		while (cmd->redirs)
		{
			expanded = expan_str(cmd->redirs->filename, data); // check if failure
			free(cmd->redirs->filename);
			cmd->redirs->filename = expanded;
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
