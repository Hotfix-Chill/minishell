/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:30 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/23 17:49:34 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strdup_export_value(t_data *data, int idx)
{
	data->export[idx].value = ft_strdup(data->export[idx + 1].value);
	if (!data->export[idx].value)
		cleanup(data, ERROR);
	return ;
}

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
				strdup_export_value(data, idx);
		}
		idx++;
	}
	if (data->export_len > 0)
		data->export_len -= 1;
	data->export = ft_realloc_export(data, data->export, data->export_len, 0);
}

void	add_env_entry(t_data *data, char *str, char *key)
{
	size_t	idx;

	data->env_len += 1;
	data->env = ft_realloc_env(data, data->env, data->env_len, -1);
	idx = data->env_len - 1;
	data->env[idx] = ft_strdup(str);
	if (!data->env[idx])
	{
		free(key);
		cleanup(data, ERROR);
	}
}

bool	check_entry_env(t_data *data, char *key, char *str)
{
	size_t	idx;

	idx = 0;
	while (data->env[idx])
	{
		if (ft_memcmp(data->env[idx], key, ft_strlen(key) + 1) == 61)
		{
			free(data->env[idx]);
			data->env[idx] = ft_strdup(str);
			if (!data->env[idx])
			{
				free(key);
				cleanup(data, ERROR);
			}
			return (true);
		}
		idx++;
	}
	return (false);
}
