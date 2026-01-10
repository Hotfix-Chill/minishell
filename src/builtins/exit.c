/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:06:32 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/12 14:20:16 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	digit_check(t_cmds *cmd, t_data *data)
{
	int	i;
	int j;

	j = 0;
	if (cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
		j++;
	i = j;
	while (cmd->argv[1][i])
	{
		if (!ft_isdigit(cmd->argv[1][i]))
		{
			fprintf(stderr, "exit\nminishell: exit: ");
			fprintf(stderr, "%s: numeric argument required\n", cmd->argv[1]);
			cleanup(data, 2);
		}
		i++;
	}
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	long long nb;

	fprintf(stderr, "exit\n");
	if (!cmd->argv[1])
		cleanup(data, data->return_value);
	digit_check(cmd, data);
	if (ll_overflow_check(cmd->argv[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
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
