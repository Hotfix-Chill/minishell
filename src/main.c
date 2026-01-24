/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2026/01/24 15:08:31 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

bool	is_only_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&data->fd, -1, sizeof(t_fds));
	return (1);
}

int	main_loop(char *line, t_data	*data)
{
	t_token_list *tokens;

	while (1)
	{
		line = readline(PROMPT);
		if (!line) // NULL → Ctrl+D pressed (EOF)
			return (printf("exit\n"), cleanup(data, OK_EXIT), 0);
		if (*line) // not empty input
		{
			if (*line != SPACE)
				add_history(line);
			if (is_only_whitespaces(line))
			{
				add_history(line);
				free(line);
				continue;
			}
			tokens = tokenizer(line);
			if (!tokens)
			{
				printf("minishell: syntax error\n");
				free(line);
				data->return_value = 1;
				continue ;
			}
			if (VERBOSE)
				print_token_list(tokens);

			// PARSING
			data->list = parsing(tokens, data);
			if (!data->list)
			{
				printf("minishell: syntax error\n");
				free_token_list(tokens);
				free(line);
				data->return_value = 2;
				continue ;
			}
 			if (VERBOSE)
			{
				print_cmd_list(data->list->head);
				printf("data_list_size: %i\n", data->list->size);
			}
			free_token_list(tokens);

			if (VERBOSE)
				printf("INSIDE HEREDOC\n");
			if (heredocs(data, data->list->head) == SIGINT)
			{
				free(line);
				data->return_value = 130;
				continue ;
			}
			expansion(data->list, data);
			word_splitting(data->list, data);
			update_builtins(data->list);
			executor(data->list->head, data);
			if (VERBOSE)
				printf("INSIDE MAIN LOOP CLEANUP\n");
			cleanup(data, RESET);
		}
		free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	line = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	if (!!init_signals_prompt() || !init_data(&data) || !init_env(envp, &data))
		cleanup(&data, 1);
	main_loop(line, &data);
	rl_clear_history();
	return (0);
}
