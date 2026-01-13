/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:06:18 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/10 15:06:51 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_free(char **tmp, char **arr)
{
	if (*arr)
		free(*arr);
	if (*tmp)
		free(*tmp);
}

void	change_pwd_path(t_data *data, char *path)
{
	int		i;
	char	*curr_dir;
	char	*tmp;

	i = 0;
	curr_dir = NULL;
	tmp = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			curr_dir = getcwd(NULL, 0);
			printf("dir: %s\npath: %s\n", curr_dir, path);
			tmp = ft_strjoin(curr_dir, "/");
			data->pwd = ft_strjoin(tmp, path);
			printf("pwd: %s\n", data->pwd);
			if (!curr_dir || !tmp)
				break ;
			free(data->env[i]);
			data->env[i] = curr_dir;
			break ;
		}
		i++;
	}
	//save_free(&tmp, &curr_dir);
}

char	*find_home_path(t_data *data)
{
	int i;
	char *path = NULL;


	i = 0;
	printf("ENTERING FUNCT\n");
	while (data->env[i])
	{
		if (ft_memcmp(data->env[i], "HOME=", 5) == 0)
			path = ft_substr(data->env[i], 5, ft_strlen(data->env[i]));
		i++;
	}
	if (!path)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
		data->return_value = 1;
	}
	printf("EXITING FUNCT\n");
	printf("path in find>home: %s \n", path);
	return (path);
}

void	ft_cd(t_data *data, t_cmds *cmd)
{
	char *path;

	path = NULL;
	if (!cmd->argv[1])
	{
		data->pwd = find_home_path(data);
		if (!path)
			return ;
	}
	else if (cmd->argv[2])
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		data->return_value = 1;
		return ;
	}
	else
		path = getcwd(NULL, 0);
	change_pwd_path(data, cmd->argv[1]);
	printf("data INLINE pwd %s\n", data->pwd);
	if (chdir(data->pwd) == -1)
	{
		perror("minishell: cd: ");
		data->return_value = 1;
		return ;
	}
	data->pwd = NULL;
	data->return_value = 0;
}
