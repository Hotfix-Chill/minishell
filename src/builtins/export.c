/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:12:03 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/12 12:31:16 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->export_len)
	{
		printf("declare -x ");
		printf("%s", data->export[i].key);
		if (data->export[i].value)
		{
			printf("=\"");
			printf("%s", data->export[i].value);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	data->return_value = 0;
}

void	add_values(t_data *data, char *str)
{
	char	*key;
	char	*value;

	key = get_key(str, data);
	if (!key)
		cleanup(data, ERROR);
	value = get_value(data, str, key);
	if (!check_entry_export(data, key, value)) // no entry means return false
	{
		if (!add_export_entry(data, key, value))
		{
			free(key);
			if (value)
				free(value);
			cleanup(data, ERROR);
		}
	}
	if (value)
		free(value);
	if (data->flag.equal_exists && !check_entry_env(data, key, str))
	{
		add_env_entry(data, str, key);
		data->flag.equal_exists = false;
	}
	free(key);
}

bool	split_into_key_and_value(t_data *data, char *str, int idx)
{
	char **arr;

	if (!str)
		return (false);
	arr = ft_split(str, '=');
	if (!arr)
		return (false);
	data->export[idx].key = ft_strdup(arr[0]);
	if (!data->export[idx].key)
		return (free_split(arr), false);
	if (!arr[1])
		data->export[idx].value = ft_calloc(1, sizeof(char));
	else
	{
		data->export[idx].value = ft_strdup(arr[1]);
		if (!data->export[idx].value)
			return (free_split(arr), false);
	}
	free_split(arr);
	return true;
}

static bool	valid_identifier_export(char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] !=  '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}


void	ft_export(t_data *data, t_cmds *cmd)
{
	int		i;
	bool	valid;

	valid = true;
	if (!cmd->argv[1])
	{
		print_export(data);
		return ;
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (!valid_identifier_export(cmd->argv[i]))// first letter only LETTERS or _ --> after only letters, digits or _
		{
			valid = false;
			data->return_value = 1;
			printf("minishell: export: `%s': not a valid identifier\n", cmd->argv[i++]);
			continue;
		}
		add_values(data, cmd->argv[i++]);
	}
	if (valid)
		data->return_value = 0;
}
