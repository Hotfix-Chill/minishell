/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:06:32 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/13 21:56:33 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	digit_check(t_cmds *cmd, t_data *data)
{
	int	i;
	int j;

	j = 0;
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
			printf("minishell: exit: ");
			printf("%s: numeric argument required\n", cmd->argv[1]);
			cleanup(data, 2);
		}
		i++;
	}
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	long long nb;

	printf("exit\n");
	if (!cmd->argv[1])
		cleanup(data, data->return_value);
	digit_check(cmd, data);
	if (ll_overflow_check(cmd->argv[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
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
