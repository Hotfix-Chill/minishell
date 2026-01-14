/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:22:49 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/14 09:39:14 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*ft_realloc_export(t_data *data, t_export *export, size_t size, int min)
{
	size_t		i;
	t_export	*tmp;

	tmp = ft_calloc(size, sizeof(t_export));
	if (!tmp)
		cleanup(data, ERROR);
	i = 0;
	while (i < data->export_len + min)
	{
		tmp[i].key = ft_strdup(export[i].key);
		if (!export[i].value)
		{i++; continue;}
		tmp[i].value = ft_strdup(export[i].value);
		if (!tmp[i].key || !tmp[i].value)
		{
			clean_export(tmp, size);
			free(tmp);
			cleanup(data, ERROR);
		}
		i++;
	}
	clean_export(export, size + min);
	free(export);
	return (tmp);
}

char	**ft_realloc_env(t_data *data, char **env, size_t len, int min)
{
	size_t		i;
	char	**tmp;

	tmp = ft_calloc(len + 1, sizeof(char *));
	if (!tmp)
		cleanup(data, ERROR);
	i = 0;
	while (i < data->env_len + min)
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_split(tmp);
			cleanup(data, ERROR);
		}
		i++;
	}
	free_split(env);
	return (tmp);
}
