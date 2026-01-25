/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:03:35 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/23 17:49:50 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isflag_activ(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(t_data *data, t_cmds *cmd)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	data->return_value = 0;
	if (!cmd->argv[ARGS])
	{
		printf("\n");
		return ;
	}
	while (isflag_activ(cmd->argv[i]))
	{
		n_flag = true;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
