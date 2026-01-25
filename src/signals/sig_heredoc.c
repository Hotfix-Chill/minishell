/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:55:01 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/25 14:01:38 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//rl_event_hook(ioctl(STDIN_FILENO, TIOCSTI, "\n"));
void	heredoc_handler(int sig)
{
	(void) sig;
	g_signal = SIGINT;
}

static int	prompt_event_hook_heredoc(void)
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

void	init_signals_heredoc(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	rl_event_hook = prompt_event_hook_heredoc;
	sa.sa_handler = heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
