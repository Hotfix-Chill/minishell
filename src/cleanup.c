/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:07:12 by abita             #+#    #+#             */
/*   Updated: 2025/11/19 15:07:25 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	cleanup(t_data *data)
{
	if (data->env)
		free_split(data->env);
	if (data->path_list)
		free_split(data->path_list);
}
