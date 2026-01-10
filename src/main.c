/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/01 16:46:52 by pjelinek         ###   ########.fr       */
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
	t_stack *cmds;
	t_token_list *tokens;

	while (1)
	{
		line = readline(prompt);
		if (!line) // NULL → Ctrl+D pressed (EOF)
			return (fprintf(stderr, "exit\n"), cleanup(&data, OK_EXIT), 0);
		if (*line) // not empty input
		{
			if (*line != SPACE)
				add_history(line);
<<<<<<< HEAD

			//tokens = lexer(line);
			//cmd = parser(tokens);
			if (VERBOSE  || DEBUG_ALLOC)
				debug_build_commands(&data);
			print_cmd_list(data.list.head);

			fprintf(stderr, "data_list_size: %i\n", data.list.size);

			if (heredocs(&data, data.list.head) == SIGINT)
=======
			tokens = tokenizer(line);
			// handeling tokenizing error incase of allocation failure
			if (!tokens)
			{
				fprintf(stderr, "token failure\n");
				free(line);
				continue ;
			}
			// success but there are no tokens :(
			// if (!tokens[0])
			// {
			// 	fprintf(stderr, "tokenizer: no tokens produced\n");
			// 	free_tokens(tokens);
			// 	free(line);
			// 	continue ;
			// }
			parsing(tokens);
			debug_build_commands(&data);
			print_cmd_list(data->list.head);
			fprintf(stderr, "data_list_size: %i\n", data->list.size);
			if (heredocs(&data, data->list.head) == SIGINT)
>>>>>>> Arsela
			{
				free(line);
				continue ;
			}
			// expansions
			executor(data->list.head, &data);
			cleanup(&data, RESET);
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
