/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:06:32 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/15 12:46:05 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	digit_check(t_cmds *cmd)
{
	int	i;
	int j;

	j = 0;
	if (!cmd->argv[1][0])
		return (false);
	if ((cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
	&& cmd ->argv[1][1] != '\0')
		j++;
	/* else if (!ft_isdigit(cmd->argv[1][0]))
	{
			printf("minishell: exit: ");
			printf("%s: numeric argument required\n", cmd->argv[1]);
			cleanup(data, 2);
	} */
	i = j;
	while (cmd->argv[1][i])
	{
		if (!ft_isdigit(cmd->argv[1][i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	long long nb;

	if (!cmd->argv[1])
	{
		if (data->list->size == 1)
			printf("exit\n");
		cleanup(data, OK_EXIT);
	}
	printf("exit\n");
	if (!digit_check(cmd) || ll_overflow_check(cmd->argv[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
		data->return_value = 2;
		cleanup(data, 2);
	}
	if (cmd->argv[2])
	{
		printf("minishell: exit: to many arguments\n");
		data->return_value = 1;
		return ;
	}
	nb = ft_atoll(cmd->argv[1]);
	data->return_value = (nb % 256 + 256) % 256;
	cleanup(data, data->return_value);
}
