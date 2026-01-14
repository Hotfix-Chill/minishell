/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:10:38 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/14 10:27:46 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_list(t_data *data)
{
	int		i;
	char	**path_list;

	i = 0;
	if (!data->env)
		return (NULL);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path_list = ft_split(&data->env[i][5], ':');
			if (!path_list)
				return (NULL);
		}
		i++;
	}
	return (path_list);
}


