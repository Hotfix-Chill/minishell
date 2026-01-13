/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:12:31 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/13 00:50:51 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_builtins(t_data *data, t_cmds *cmd)
{
	if (!cmd->argv[CMD] || !*cmd->argv[CMD] || !data->env || !*data->env)
		cleanup(data, ERROR);
	if (!cmd->builtin)
		return (false);
	if (ft_memcmp("echo", cmd->argv[CMD], 5) == 0)
		ft_echo(data, cmd);
	else if (ft_memcmp("cd", cmd->argv[CMD], 3) == 0)
		ft_cd(data, cmd);
	else if (ft_memcmp("exit", cmd->argv[CMD], 5) == 0)
		ft_exit(data, cmd);
	else if (ft_memcmp("env", cmd->argv[CMD], 4) == 0)
		ft_env(data);
	else if (ft_memcmp("pwd", cmd->argv[CMD], 4) == 0)
		ft_pwd(data);
	else if (ft_memcmp("unset", cmd->argv[CMD], 6) == 0)
		ft_unset(data, cmd);
	else if (ft_memcmp("export", cmd->argv[CMD], 7) == 0)
		ft_export(data, cmd);
	return (true);
}




void	executor(t_cmds *cmd, t_data *data)
{

	if (data->list->size == 1 && cmd->builtin)
		exec_builtins(data, cmd);
	else if (data->list->size == 1)
		single_cmd(data, cmd);
	else if (data->list->size > 1)
		multi_cmds(data, cmd);
	/* else
		return ; */
}
