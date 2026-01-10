/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/13 12:45:10 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints env struct with envp values
void	print_env(t_data *data)
{
	return ;
	int	i;

	i = 0;
	printf("\nDATA_ENV:\n\n");
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	if (data->path_list)
	{
		i = 0;
		printf("\nPATH_LIST:\n");
		while (data->path_list[i])
			printf("%s\n", data->path_list[i++]);
	}
}

void	print_exit_signals(int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		printf("\033[31m[SIGSEGV]\033[0m\n");
	else if (WTERMSIG(status) == SIGBUS)
		printf("\033[31m[SIGBUS]\033[0m\n");
	else if (WTERMSIG(status) == SIGABRT)
		printf("\033[31m[SIGABRT]\033[0m\n");
	else if (WTERMSIG(status) == SIGFPE)
		printf("\033[31m[SIGFPE]\033[0m\n");
	else if (WTERMSIG(status) == SIGPIPE)
		printf("\033[31m[SIGPIPE]\033[0m\n");
	else if (WTERMSIG(status) == SIGILL)
		printf("\033[31m[SIGILL]\033[0m\n");
}
