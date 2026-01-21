/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:06:32 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/21 19:55:54 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	digit_check(t_cmds *cmd)
{
	const char *p = cmd->argv[1];

	if (!cmd->argv[1][0])
		return (false);
	ft_skip_whitespaces(&p);
	if ((*p == '-' || *p == '+')
		&& *p + 1 != '\0')
		p++;
	while (*p)
	{
		if (!ft_isdigit(*p) && !ft_isspace(*p))
		{
			return (false);
		}
		p++;
	}
	return (true);
}

void	ft_exit(t_data *data, t_cmds *cmd)
{
	long long	nb;

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
