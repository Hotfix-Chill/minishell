/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/10 16:37:34 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char *redir_type_to_str(int type)
{
    if (type == REDIR_IN)
        return "REDIR_IN";
    if (type == REDIR_OUT)
        return "REDIR_OUT";
    if (type == REDIR_APPEND)
        return "REDIR_APPEND";
    if (type == REDIR_HEREDOC)
        return "REDIR_HEREDOC";
    return "UNKNOWN";
}




static void print_one_cmd(t_cmds *cmd, int idx)
{
    int     i;
    t_redirs *r;

    printf("cmd %d\n", idx);
    printf("  t_cmd\n");

    i = 0;
    if (cmd->argv)
    {
        while (cmd->argv[i])
        {
            printf("    argv[%d] -> \"%s\"\n", i, cmd->argv[i]);
            i++;
        }
    }
    else
        printf("    argv: (null)\n");

    r = cmd->redirs;
    i = 0;
    while (r)
    {
        printf("\n  t_redirs[%d]\n", i);
        printf("    type     -> %s\n", redir_type_to_str(r->typ));
        printf("    filename -> \"%s\"\n", r->filename ? r->filename : "(null)");
        r = r->next;
        i++;
    }
    if (!cmd->redirs)
        printf("  (no redirections)\n");

    if (cmd->pipe_after)
        printf("\n  PIPE  ---> cmd %d\n", idx + 1);

    printf("\n");
}

void print_cmd_list(t_cmds *head)
{
    int   i;
    t_cmds *cur;

    puts("======= PARSED COMMAND STRUCTURE =======\n");
    cur = head;
    i = 1;
    while (cur)
    {
        print_one_cmd(cur, i);
        cur = cur->next;
        i++;
    }
    puts("========================================");
}

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
