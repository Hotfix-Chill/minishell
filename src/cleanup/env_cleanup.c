/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:16:37 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 00:19:05 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cleanup(t_data *data, int exit_code)
{
	if (data->env && exit_code != RESET)
	{
		free_split(data->env);
		data->env = NULL;
	}
	if (data->path_list)
	{
		free_split(data->path_list);
		data->path_list = NULL;
	}
	if (data->export && exit_code != RESET)
	{
		clean_export(data->export, data->export_len);
		free(data->export);
		data->export = NULL;
	}
	return ;
}
