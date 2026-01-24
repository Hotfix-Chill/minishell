/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2026/01/24 16:33:30 by pjelinek         ###   ########.fr       */
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

bool	parser(t_data *data, char *line)
{
	t_token_list	*tokens;

	tokens = tokenizer(line);
	if (!tokens)
	{
		printf("minishell: syntax error\n");
		free(line);
		data->return_value = 1;
		return (false);
	}
	data->list = parsing(tokens, data);
	if (!data->list)
	{
		printf("minishell: syntax error\n");
		free_token_list(tokens);
		free(line);
		data->return_value = 2;
		return (false);
	}
	free_token_list(tokens);
	return (true);
}

bool	execution(t_data *data, char *line)
{
	if (heredocs(data, data->list->head) == SIGINT)
	{
		free(line);
		data->return_value = 130;
		return (false);
	}
	expansion(data->list, data);
	word_splitting(data->list, data);
	update_builtins(data->list);
	executor(data->list->head, data);
	return (true);
}

int	main_loop(char *line, t_data	*data)
{
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			return (printf("exit\n"), cleanup(data, OK_EXIT), 0);
		if (*line)
		{
			if (*line != SPACE)
				add_history(line);
			if (is_only_whitespaces(line))
			{
				free(line);
				continue ;
			}
			if (!parser(data, line) || execution(data, line))
				continue ;
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
