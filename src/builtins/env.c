/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:01:49 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/15 04:32:51 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->argv[1])
	{
		data->return_value = 127;
		printf("env: '%s': No such file or dierectory\n", cmd->argv[1]);
		return ;
	}
	while (data->env && data->env[i])
	{
		printf("%s\n", data->env[i++]);
	}
	data->return_value = 0;
}
