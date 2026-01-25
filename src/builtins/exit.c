/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:06:32 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/22 17:42:30 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	num_arg(t_data *data, char *str)
{
	printf("minishell: exit: %s: numeric argument required\n", str);
	data->return_value = 2;
	free(str);
	cleanup(data, 2);
	return ;
}

static bool	digit_check(t_cmds *cmd)
{
	const char	*p = cmd->argv[1];

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
	char		*trimm;

	if (!cmd->argv[1])
	{
		if (data->list->size == 1)
			printf("exit\n");
		cleanup(data, OK_EXIT);
	}
	printf("exit\n");
	trimm = ft_strtrim(cmd->argv[1], WHITESPACES);
	if (!digit_check(cmd) || ll_overflow_check(trimm))
		num_arg(data, trimm);
	if (cmd->argv[2])
	{
		printf("minishell: exit: to many arguments\n");
		data->return_value = 1;
		free(trimm);
		return ;
	}
	nb = ft_atoll(trimm);
	data->return_value = (nb % 256 + 256) % 256;
	free(trimm);
	cleanup(data, data->return_value);
}
