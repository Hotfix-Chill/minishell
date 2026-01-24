/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:49:20 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 13:47:29 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	redirs_lstclear(t_redirs **lst)
{
	t_redirs	*redirs;
	t_redirs	*next;

	if (!lst || !*lst)
		return ;
	redirs = *lst;
	while (redirs)
	{
		next = redirs->next;
		free(redirs->filename);
		free(redirs);
		redirs = next;
	}
	*lst = NULL;
}

void	cmd_lstclear(t_cmds **lst)
{
	t_cmds	*cmd;
	t_cmds	*next;

	if (!lst || !*lst)
		return ;
	cmd = *lst;
	while (cmd)
	{
		next = cmd->next;
		free_split(cmd->argv);
		redirs_lstclear(&cmd->redirs);
		free(cmd);
		cmd = next;
	}
	*lst = NULL;
}

void	clean_export(t_export *export, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (export[i].key)
		{
			free(export[i].key);
			export[i].key = NULL;
		}
		if (export[i].value)
		{
			free(export[i].value);
			export[i].value = NULL;
		}
		i++;
	}
}

void	cleanup(t_data *data, int exit_code)
{
	env_cleanup(data, exit_code);
	executor_cleanup(data);
	if (data->heredoc.files)
		ft_heredoc_cleanup(data);
	ft_memset(&data->fd, -1, sizeof(t_fds));
	ft_memset(&data->list, 0, sizeof(t_list));
	g_signal = 0;
	if (exit_code == RESET)
		return ;
	data->return_value = exit_code;
	rl_clear_history();
	exit(exit_code);
}
