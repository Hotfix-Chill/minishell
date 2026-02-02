/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:05:22 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/23 17:50:13 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_env_entry(t_data *data, size_t idx)
{
	while (data->env[idx])
	{
		free(data->env[idx]);
		data->env[idx] = NULL;
		if (data->env[idx + 1])
		{
			data->env[idx] = ft_strdup(data->env[idx + 1]);
			if (!data->env[idx])
				cleanup(data, ERROR);
		}
		idx++;
	}
	if (data->env_len > 0)
		data->env_len -= 1;
	data->env = ft_realloc_env(data, data->env, data->env_len, 0);
}

void	delete_entries(t_data *data, t_cmds *cmd, size_t idx)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(cmd->argv[idx]);
	while (data->env[i])
	{
		if (ft_memcmp(data->env[i], cmd->argv[idx], len + 1) == 61)
		{
			delete_env_entry(data, i);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data->export_len)
	{
		if (ft_memcmp(data->export[i].key, cmd->argv[idx],
				ft_strlen(cmd->argv[idx]) + 1) == 0)
		{
			delete_export_entry(data, i);
			break ;
		}
		i++;
	}
}

static bool	valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	ft_unset(t_data *data, t_cmds *cmd)
{
	size_t	j;

	j = 1;
	while (cmd->argv[j])
	{
		if (!valid_identifier(cmd->argv[j]))
		{
			j++;
			continue ;
		}
		delete_entries(data, cmd, j);
		j++;
	}
	data->return_value = 0;
}
