/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:30 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/16 07:21:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str, t_data *data)
{
	int equal = find_char(str, '=');
	if (equal == -1)
		return (ft_strdup(str));
	data->flag.equal_exists = true;
	return (ft_substr(str, 0, equal));
}

char	*get_value(t_data *data, char *str, char *key)
{
	int		equal;
	char	*tmp;
	char	*value;

	equal = find_char(str, '=');
	if (equal == -1)
		return (NULL);
	if (str[equal + 1] == '\0')
		return (ft_calloc(1, sizeof(char)));
	tmp = ft_substr(str, equal + 1, ft_strlen(str));
	if (!tmp)
		return (free(key), cleanup(data, ERROR), NULL);
	value = ft_strtrim(tmp, "\"");
	free(tmp);
	if (!value)
		return (free(key), cleanup(data, ERROR), NULL);
	return (value);
}

bool	add_export_entry(t_data *data, char *key, char *value)
{
	size_t		idx;

	data->export_len += 1;
	data->export = ft_realloc_export(data, data->export, data->export_len, -1);
	idx = data->export_len - 1;
	data->export[idx].key = ft_strdup(key);
	if (!data->export[idx].key)
		return (false);
	if (!value)
		data->export[idx].value = NULL;
	else
	{
		data->export[idx].value = ft_strdup(value);
		if (!data->export[idx].value)
			return (false);
	}
	return (true);
}

bool	check_entry_export(t_data *data, char *key, char *value)
{
	size_t i;

	i = 0;
	while (i < data->export_len)
	{
		if (ft_memcmp(data->export[i].key, key, ft_strlen(key) + 1) == 0)
		{
			if (data->export[i].value)
				free(data->export[i].value);
			if (!value)
				data->export[i].value = NULL;
			else
			{
				data->export[i].value = ft_strdup(value);
				if (!data->export[i].value)
					cleanup(data, ERROR);
			}
			return (true);
		}
		i++;
	}
	return (false);
}
