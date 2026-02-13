/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:55:01 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/05 21:52:49 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static int	prompt_event_hook(void)
{
	if (g_signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	*init_signals_prompt(void)
{
	struct sigaction	sa;

	rl_event_hook = prompt_event_hook;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = prompt_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (NULL);
}
