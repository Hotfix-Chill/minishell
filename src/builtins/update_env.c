/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:30 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/21 18:11:19 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
