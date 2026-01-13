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


char *expan_str(const char *args, t_data *data)
{
	int i;
	char *result;
	(void)data;

	result = ft_strdup(""); //.. start w empty str
	printf("ENTER EXPAN_STR\n");
	i = 0;
	while (args[i])
	{
		if (args[i] == '$' && (!ft_isspace(args[i + 1]) || args[i + 1] != '\0'))
		{
			if (args[i + 1] == '?' )
			{
				printf("%u\n", data->return_value);
				return (NULL);
			}
			result = ft_strdup(args + 1);
			printf("new_var: %s\n", result);
		}
		i++;
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], result, ft_strlen(result) + 1) == 61)
		{
			take data->[i] entry and loop to '=' and the substring after = and save it into
		}
		i++;
	}
	printf("EXITING EXPAN_STR\n");
	return (result);
}

int expansion(t_stack *cmd_list, t_data *data)
{
	int i;
	char *expanded;
	t_cmds *cmd;

	if (!cmd_list || !data)
		return (EXIT_FAILURE);
	i = 0;
	cmd = cmd_list->head;
	printf("ENTER\n");
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
		// while (cmd->redirs)
		// {
		// 	expanded = expan_str(cmd->redirs->filename, data); // check if failure
		// 	free(cmd->redirs->filename);
		// 	cmd->redirs->filename = expanded;
		// 	cmd->redirs = cmd->redirs->next;
		// }
		cmd = cmd->next;
	}
	printf("EXITING\n");
	return (EXIT_SUCCESS);
}
