/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2026/01/10 17:06:09 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&data->fd, -1, sizeof(t_fds));
	return (1);
}
int	main_loop(char *line, char	*prompt, t_data	*data)
{
	t_token_list *tokens;

	while (1)
	{
		line = readline(prompt);
		if (!line) // NULL → Ctrl+D pressed (EOF)
			return (printf("exit\n"), cleanup(data, OK_EXIT), 0);
		if (*line) // not empty input
		{
			if (*line != SPACE)
				add_history(line);
			tokens = tokenizer(line);
			// handeling tokenizing error incase of allocation failure
			if (!tokens)
			{
				printf("token failure\n");
				free(line);
				continue ;
			}
			printf("INSIDE PARSING\n");

			data->list = parsing(tokens);

			if (!data->list->head)
				cleanup(data, OK_EXIT);




			if (VERBOSE)
			{
				print_cmd_list(data->list->head);
				printf("data_list_size: %i\n", data->list->size);
			}
			printf("INSIDE HEREDOC\n");

			// if (heredocs(data, data->list->head) == SIGINT)
			// {
			// 	free(line);
			// 	data->return_value = 130;
			// 	continue ;
			// }

			// expansions

			printf("INSIDE EXECUTOR\n");

			executor(data->list->head, data);
			cleanup(data, RESET);
		}
		free(line);
	}
}
// main
int	main(int ac, char **av, char **envp)
{
	char	*prompt;
	char	*line;
	t_data	data;

	line = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	prompt = "\001\033[1;32m\002❯ \001\033[1;37m\002minishell\001\033[0m\002 ▸ $ ";
	if (!!init_signals_prompt() || !init_data(&data) || !init_env(envp, &data))
		cleanup(&data, 1);
	//// main looop version
	main_loop(line, prompt, &data);
	return (0);
}
