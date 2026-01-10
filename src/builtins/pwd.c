/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:55:40 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/09 14:13:01 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		cleanup(data, ERROR);
	fprintf(stderr,"%s\n", pwd);
	free(pwd);
	data->return_value = 0;
}
