/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:13:33 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/15 00:46:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_data *data, int pid)
{
	int	status;
	int exit_code;
	pid_t	wpid;

	exit_code = 0;
	init_signals_parent();
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
			if (VERBOSE)
				print_exit_signals(status);
		}
		wpid = wait(&status);
	}
	init_signals_prompt();
	data->return_value = exit_code;				// use for $? in expander
	if (VERBOSE)
		printf("ExitCode: %i\n", data->return_value);
}
void	ft_close(t_data *data)
{
	if (data->fd.prev[0] >= 0)
		close(data->fd.prev[0]);
	if (data->fd.prev[1] >= 0)
		close(data->fd.prev[1]);
	if (data->fd.curr[0] >= 0)
		close(data->fd.curr[0]);
	if (data->fd.curr[1] >= 0)
		close(data->fd.curr[1]);
	ft_memset(&data->fd, -1, sizeof(t_fds));
	return ;
}

static void	child_process(t_data *data, t_cmds *cmd, int loop)
{
	if (loop == 0) // 1ST Loop, redir pipe to stdout
	{
		if (dup2(data->fd.curr[1], STDOUT_FILENO) < 0)
		{
			child_cleanup(1, "child[1] - dup2 fd.curr failed\n", data, cmd);
		}
	}
	else if (loop > 0 && loop < data->list.size - 1)  // IN BETWEEN cmd 2 - (n-1)
	{
		if (dup2(data->fd.prev[0], STDIN_FILENO) < 0)
			child_cleanup(1, "child - dup2 fd.prev[0] failed\n", data, cmd);
		if (dup2(data->fd.curr[1], STDOUT_FILENO) < 0)
			child_cleanup(1, "child - dup2 fd.curr[1]] failed\n", data, cmd);
	}
	else if (loop == data->list.size - 1) // Last COMMAND
	{
		if (dup2(data->fd.prev[0], STDIN_FILENO) < 0)
			child_cleanup(1, "child[last] - dup2 fd.prev[0] failed\n", data, cmd);
	}
	ft_close(data);
	exec_cmd(data, cmd);
}


static void	parent_process(t_data *data, t_cmds *cmd, int loop)
{
	if (close(data->fd.prev[0]) < 0 || close(data->fd.prev[1]) < 0)
		child_cleanup(1, "parent - close fd.prev failed\n", data, cmd);
	if (loop != data->list.size - 1)
	{
		data->fd.prev[0] = data->fd.curr[0];
		data->fd.prev[1] = data->fd.curr[1];
	}
	ft_memset(&data->fd.curr, -1, sizeof(data->fd.curr));
}

void	multi_cmds(t_data *data, t_cmds *cmd)
{

	int		i;
	pid_t	pid;

	pid = 0;
	if (pipe(data->fd.prev) < 0)
		child_cleanup(1, "open pipe fd.prev failed\n", data, cmd);
	i = 0;
	while (i < data->list.size)
	{
		if (i != data->list.size - 1)
			if (pipe(data->fd.curr) < 0)
				child_cleanup(1, "pipe fd.curr failed\n", data, cmd);
		pid = fork();
		if (pid < 0)
			child_cleanup(1, "error fork\n", data, cmd);
		if (pid == 0)
			child_process(data, cmd, i);
		else
			parent_process(data, cmd, i);
		if (cmd->next != NULL)
			cmd = cmd->next;
		i++;
	}
	get_exit_status(data, pid);
}
