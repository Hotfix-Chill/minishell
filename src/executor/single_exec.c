/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:42:02 by netrunner         #+#    #+#             */
/*   Updated: 2026/02/02 14:20:48 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_relative_path(t_data *data, t_cmds *cmd)
{
	int	error_code;

	error_code = 0;
	if (!cmd->argv[0][3])
		child_cleanup(126, " : is a directory\n", data, cmd);
	if (access(cmd->argv[0], X_OK) == -1)
	{
		error_code = errno;
		handle_errno(data, cmd, error_code);
	}
	if (execve(cmd->argv[0], cmd->argv, data->env) == -1)
	{
		error_code = errno;
		handle_errno(data, cmd, error_code);
	}
}

static void	apply_execve(t_data *data, t_cmds *cmd)
{
	int	error_code;

	error_code = 0;
	if (access(data->exec.path, F_OK) == 0)
	{
		if (access(data->exec.path, X_OK) == 0)
		{
			execve(data->exec.path, cmd->argv, data->env);
			error_code = errno;
			free(data->exec.path);
			handle_errno(data, cmd, error_code);
		}
		else
			child_cleanup(126, " : Permission denied\n", data, cmd);
	}
}

static char	*ft_path(char *dir, char *cmd_line, t_data *data, t_cmds *cmd)
{
	char	*tmp;
	char	*full_path;

	if (!cmd_line || !cmd_line[0] || !*cmd_line)
		child_cleanup(127, " \"\" : empty command not found\n", data, cmd);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd_line);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	exec_cmd(t_data *data, t_cmds *cmd)
{
	int		i;

	i = 0;
	init_signals_child();
	if (!!cmd->redirs)
		handle_redirections(data, cmd);
	if (!*cmd->argv || exec_builtins(data, cmd))
		cleanup(data, data->return_value);
	if (ft_strchr(cmd->argv[0], '/') || (cmd->argv[0][0] == '.'
		&& cmd->argv[0][1] == '/' ))
		execute_relative_path(data, cmd);
	data->path_list = get_path_list(data, cmd);
	if (!data->path_list)
		child_cleanup(127, ": command not found\n", data, cmd);
	while (data->path_list[i])
	{
		data->exec.path = ft_path(data->path_list[i], cmd->argv[0], data, cmd);
		if (!data->exec.path)
			child_cleanup(1, " : malloc error single_exec.c \n", data, cmd);
		apply_execve(data, cmd);
		free(data->exec.path);
		i++;
	}
	child_cleanup(127, ": command not found\n", data, cmd);
}

void	single_cmd(t_data *data, t_cmds *cmd)
{
	int	pid;

	if (VERBOSE)
		printf("INSIDE SINGLE CMD\n");
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		exec_cmd(data, cmd);
	else
		get_exit_status(data, pid);
}
