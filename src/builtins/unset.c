/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:05:22 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/16 06:43:21 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_export_entry(t_data *data, size_t idx)
{
	while (idx < data->export_len)
	{
		free(data->export[idx].key);
		data->export[idx].key = NULL;
		if (data->export[idx].value)
		{
			free(data->export[idx].value);
			data->export[idx].value = NULL;
		}
		if (idx + 1 != data->export_len)
		{
			data->export[idx].key = ft_strdup(data->export[idx + 1].key);
			if (!data->export[idx].key)
				cleanup(data, ERROR);
			if (data->export[idx].value == NULL)
				data->export[idx].value = NULL;
			else
			{
				data->export[idx].value = ft_strdup(data->export[idx + 1].value);
				if (!data->export[idx].value)
					cleanup(data, ERROR);
			}
		}
		idx++;
	}
	if (data->export_len > 0)
		data->export_len -= 1;
	data->export = ft_realloc_export(data, data->export, data->export_len, 0);

}

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

void	delete_entries(t_data *data, t_cmds * cmd, size_t idx)
{
	size_t i;
	size_t	len;

	i = 0;
	len = ft_strlen(cmd->argv[idx]);
	while (data->env[i])
	{
		if (ft_memcmp(data->env[i], cmd->argv[idx], len + 1) == EQUAL_VS_NULL_TERM )
		{
			delete_env_entry(data, i);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data->export_len)
	{
		if (ft_memcmp(data->export[i].key, cmd->argv[idx], ft_strlen(cmd->argv[idx]) + 1) == 0)
		{
			delete_export_entry(data, i);
			break ;
		}
		i++;
	}
}

// first letter only LETTERS or _ --> after only letters, digits or _
static bool	valid_identifier(char *str)
{
	int i;

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
	size_t j;

	j = 1;
	while (cmd->argv[j])
	{
		if (!valid_identifier(cmd->argv[j]))// first letter only LETTERS or _ --> after only letters, digits or _
		{
			j++;
			continue;
		}
		delete_entries(data, cmd, j);
		j++;
	}
	data->return_value = 0;
}
