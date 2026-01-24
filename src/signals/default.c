/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:55:01 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 14:55:27 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_handler(int sig)
{
	(void) sig;
	if (VERBOSE)
		write(1, "\n(CTRL + C) Prompt Code: 130\n", 30);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 0;
}

void	*init_signals_prompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = prompt_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (NULL);
}
