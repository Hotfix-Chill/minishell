/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/23 23:59:15 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//prints env struct with envp values
void	print_env(t_data *data)
{
	int	i;

	i = 0;
	printf("\nDATA_ENV:\n\n");
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	if (data->path_list)
	{
		i = 0;
		printf("\nPATH_LIST:\n");
		while (data->path_list[i])
			printf("%s\n", data->path_list[i++]);
	}
}

void	init_single_command_struct(t_data *data)
{
	data->list.size = 1;
	char *command_line = ft_strdup("cat");

	t_cmds *cmd = ft_calloc(1, sizeof(t_cmds));
	cmd->argv = ft_split(command_line, ' ');
	int i = 0;
	while (cmd->argv[i])
		printf("\n\nARGV: %s\n", cmd->argv[i++]);
	cmd->redirs = ft_calloc(1, sizeof(t_redirs));

	/////REDIR_IN 	<filename
	cmd->redirs->typ = REDIR_IN;
	cmd->redirs->filename = ft_strdup("Makefile");

	/////REDIR_OUT >filename
	/* cmd->redirs->next = ft_calloc(1, sizeof(t_redirs));
	cmd->redirs->next->typ = REDIR_OUT;
	cmd->redirs->next->filename = ft_strdup("out"); */

	/////REDIR_APPEND >>filename
	cmd->redirs->next = ft_calloc(1, sizeof(t_redirs));

	cmd->redirs->next->typ = REDIR_APPEND;
	cmd->redirs->next->filename = ft_strdup("out");


	/* cmd->redirs->next = ft_calloc(1, sizeof(t_redirs));
	cmd->redirs->next->typ = REDIR_IN;
	cmd->redirs->next->filename = ft_strdup("doc.txt"); */




	cmd->redirs->next->next = NULL; // 2 REDIRS
	//cmd->redirs->next = NULL; ///SINGLE REDIR
	cmd->next = NULL;

	printf("\n\n\n\n");

	printf("INPUT: cat <Makefile >> out\n\n");

	debug_executor(cmd, data);
	exit(0);
}
