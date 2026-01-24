/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:21:36 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 00:29:52 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor_cleanup(t_data *data)
{
	t_cmds *cmd;

	cmd = data->cmd;
	if (cmd)
	{
		cmd_lstclear(&cmd);
		ft_memset(&data->cmd, 0, sizeof(t_cmds));
	}
	if (data->list)
	{
		free_cmd_list(data->list);
		data->list = NULL;
	}
	return ;
}
