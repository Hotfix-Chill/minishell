	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/27 22:44:52 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add SHLVL, PWD, _= to environment if they have been removed by command env -u SHLVL
static bool	add_env(t_data *data, int i)
{
	char *str;

	if (!data->flag.shlvl)
	{
		i++;
		data->env[i] = ft_strdup("SHLVL=1");
		if (!data->env[i] || !split_into_key_and_value(data, data->env[i], i))
			return (false);
	}
	if (!data->flag.pwd)
	{
		i++;
		str = getcwd(NULL, 0);
		if (!str)
			return (false);
		data->env[i] = ft_strjoin("PWD=", str);
		free(str);
		if (!data->env[i] || !split_into_key_and_value(data, data->env[i], i))
			return (false);
	}
	if (!data->flag.last_cmd)
	{
		i++;
		data->env[i] = ft_strdup("_=/usr/bin/env");
		if (!data->env[i] || !split_into_key_and_value(data, data->env[i], i))
			return (false);
	}
	return (true);
}

//counts envp for allocation and checks if SHLVL, PWD, and _= existis and if not it counts i for later allocation!
static int	count_lines(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			data->flag.shlvl = true;
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			data->flag.pwd = true;
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			data->flag.last_cmd = true;
		i++;
	}
	if (!data->flag.shlvl)
		i++;
	if (!data->flag.pwd)
		i++;
	if (!data->flag.last_cmd)
		i++;
	return (i);
}
//copies enviroment from envp to data->env[i]
static bool	extract_env(t_data *data, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			data->env[i] = increment_shlvl(envp[i]);
		else
			data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (false);
		if (!split_into_key_and_value(data, data->env[i], i))
			return (false);
		i++;
	}
	if (!add_env(data, i - 1))
		return (false);
	return (true);
}
bool	create_export_list(t_data *data)
{
	data->export[PWD].key = ft_strdup("PWD");
	if (!data->export[PWD].key)
		return (false);
	data->export[PWD].value = getcwd(NULL, 0);
	if (!data->export[PWD].value)
		return (false);
	data->export[SHLVL].key = ft_strdup("SHLVL");
	if (!data->export[SHLVL].key)
		return (false);
	data->export[SHLVL].value = ft_strdup("1");
	if (!data->export[SHLVL].value)
		return (false);
	data->export[LAST_CMD].key = ft_strdup("_");
	if (!data->export[LAST_CMD].key)
		return (false);
	data->export[LAST_CMD].value = ft_strdup("/usr/bin/env");
	if (!data->export[LAST_CMD].value)
		return (false);
	return (true);
}

//creates environment if envp is empty
static bool	create_env(t_data *data)
{
	char	**env;
	char	*str;

	env = data->env;
	str = getcwd(NULL, 0);
	if (!str)
		return (false);
	env[PWD] = ft_strjoin("PWD=", str);
	free(str);
	if (!env[PWD])
		return (false);
	env[SHLVL] = ft_strdup("SHLVL=1");
	if (!env[SHLVL])
		return (false);
	env[LAST_CMD] = ft_strdup("_=/usr/bin/env");
	if (!env[LAST_CMD])
		return (false);
	if (!create_export_list(data))
		return (false);
	return (true);
}

//fills selfmade data->env struct with envp values
bool	init_env(char **envp, t_data *data)
{
	if (!envp || !*envp)
	{
		data->env_len = 3;
		data->export_len = data->env_len;
		data->env = ft_calloc(data->env_len + 1, sizeof(char *));
		if (!data->env)
			return (false);
		data->export = ft_calloc(data->export_len, sizeof(t_export));
		if (!data->export || !create_env(data))
			return (false);
	}
	else
	{
		data->env_len = count_lines(data, envp);
		data->export_len = data->env_len;
		data->env = ft_calloc(data->env_len + 1, sizeof(char *));
		data->export = ft_calloc(data->export_len, sizeof(t_export));
		if (!data->env || !data->export	|| !extract_env(data, envp))
			return (false);
	}
	if (VERBOSE)
		print_env(data);
	return (true);
}
