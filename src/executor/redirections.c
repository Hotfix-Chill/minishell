/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:22:18 by netrunner         #+#    #+#             */
/*   Updated: 2026/01/25 17:47:40 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redir(t_data *data, char *file, int token)
{
	int	fd;

	fd = -1;
	if (token == REDIR_APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			data->flag.redirect_fail = true;
	}
	else if (token == REDIR_OUT)
	{
		if (!file || !*file)
			return ;
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			data->flag.redirect_fail = true;
	}
	else if (token == REDIR_IN)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			data->flag.redirect_fail = true;
	}
	if (fd >= 0)
		close(fd);
}

void	handle_redirections(t_data *data, t_cmds *cmd)
{
	t_redirs	*curr;

	curr = cmd->redirs;
	if (!cmd->redirs)
		return ;
	while (curr != NULL)
	{
		if (!*curr->filename)
		{
			data->flag.redirect_fail = true;
			child_cleanup(1, ": No such file or directory\n", data, cmd);
		}
		else if (curr->typ == REDIR_APPEND)
			apply_redir(data, curr->filename, REDIR_APPEND);
		else if (curr->typ == REDIR_IN)
		{
			apply_redir(data, curr->filename, REDIR_IN);
		}
		else if (curr->typ == REDIR_OUT)
			apply_redir(data, curr->filename, REDIR_OUT);
		if (data->flag.redirect_fail == true)
		{
			perror(curr->filename);
			child_cleanup(1, NULL, data, cmd);
		}
		curr = curr->next;
	}
}
