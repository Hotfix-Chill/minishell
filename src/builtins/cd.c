/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:06:18 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/02 23:21:25 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_free(char **arr)
{
	if (*arr)
		free(*arr);
}

void	change_pwd_path(t_data *data)
{
	int		i;
	char	*dir;
	char	*pwd;

	i = 0;
	dir = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			dir = getcwd(NULL, 0);
			pwd = ft_strjoin("PWD=", dir);
			if (!dir || !pwd)
				break ;
			printf("ENV: %s\n", data->env[i]);
			free(data->env[i]);
			data->env[i] = pwd;
			printf("PWD: %s\n", data->env[i]);
			break ;
		}
		i++;
	}
	save_free(&dir);
	data->return_value = 0;
}

char	*find_home_path(t_data *data)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_memcmp(data->env[i], "HOME=", 5) == 0)
			path = ft_substr(data->env[i], 5, ft_strlen(data->env[i]));
		i++;
	}
	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		data->return_value = 1;
	}
	return (path);
}

void	ft_cd(t_data *data, t_cmds *cmd)
{
	char	*path;

	path = NULL;
	if (!cmd->argv[1])
	{
		path = find_home_path(data);
		if (!path)
			return ;
	}
	else if (cmd->argv[2])
	{
		printf("minishell: cd: too many arguments\n");
		data->return_value = 1;
		return ;
	}
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
	{
		write (2, "minishell: cd: ", 14);
		perror(path);
		data->return_value = 1;
		return ;
	}
	change_pwd_path(data);
}
