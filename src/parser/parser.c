/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:52 by abita             #+#    #+#             */
/*   Updated: 2025/12/17 17:38:20 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void print_all_commands(t_stack *cmd_list);
void print_command(t_cmds *cmd, int index);
void print_redirs(t_redirs *redirs);


/*
	P​arser that processes the tokens according to a grammar 
	and build the command table.

	Parser's Job:

	1. Group tokens into commands (split by pipes)
	2. Separate arguments from redirections
	3. Build t_cmds nodes
	4. Link them in a list


	Implement init_cmd_list(), create_cmd(), free_cmd_list()
*/

		/*
		Example:
		Token: "echo"
		Before: current_cmd->argv = NULL
		After:  current_cmd->argv = ["echo", NULL]

		Token: "hello"
		Before: current_cmd->argv = ["echo", NULL]
		After:  current_cmd->argv = ["echo", "<<", "file name", NULL]
		
		*/

// taking the tooken list from the header
t_stack *parsing(t_token_list *token)
{
	t_token			*tok;
	t_cmds			*curr_cmd;
	t_stack			*cmd_list;

	cmd_list = init_cmd_list();
	if (!cmd_list)
		return (NULL);
	curr_cmd = create_cmds();
	if (!curr_cmd)
		return (NULL);
	tok = token->head; 
	while (tok)
	{
		if (tok->typ == TOKEN_PIPE)
		{
			curr_cmd->pipe_after = true;
			if (add_cmd_to_list(cmd_list, curr_cmd) != EXIT_SUCCESS)
				return (NULL);
			curr_cmd = create_cmds();
		}
		else if(tok->typ == TOKEN_REDIR)
		{
			add_redir_to_cmd(curr_cmd, tok, tok->next);
			tok = tok->next;
		}
		else if (tok->typ == TOKEN_WORD)
			add_arg_to_cmd(curr_cmd, tok->content);
		tok = tok->next;
	}
	add_cmd_to_list(cmd_list, curr_cmd);
	return (cmd_list);
}

// int main(void)
// {
// 	t_stack *cmd_list;
// 	t_token_list *tokens;
// 	char *input;

// 	while (1)
// 	{
// 		input = readline( "lexer> " );
				
// 		add_history(input);
// 		tokens = tokenizer(input);
// 		cmd_list = parsing(tokens);


// 		// walk commands
// 		t_cmds *cmd = cmd_list->head;
// 		while (cmd)
// 		{
// 			for (int i = 0; cmd->argv && cmd->argv[i]; i++)
// 				printf("the cmd: %s\n", cmd->argv[i]);

// 			cmd = cmd->next;
// 		}
// 	}
// }

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void print_redirs(t_redirs *redirs)
{
    while (redirs)
    {
        printf("  Redir: type=%d filename='%s' heredoc=%s\n",
               redirs->typ,
               redirs->filename,
               redirs->heredoc ? "true" : "false");
        redirs = redirs->next;
    }
}

// Helper function to print a single command
void print_command(t_cmds *cmd, int index)
{
    int i;

    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  COMMAND %d\n", index);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Print argv
    printf("  Arguments (argv):\n");
    if (!cmd->argv || !cmd->argv[0])
    {
        printf("    (no arguments)\n");
    }
    else
    {
        i = 0;
        while (cmd->argv[i])
        {
            printf("    [%d] \"%s\"\n", i, cmd->argv[i]);
            i++;
        }
    }
    
    // Print redirections
    printf("\n  Redirections:\n");
    if (!cmd->redirs)
    {
        printf("    (no redirections)\n");
    }
    else
    {
        print_redirs(cmd->redirs);
    }
    
    // Print pipe flag
    printf("\n  Pipe after: %s\n", cmd->pipe_after ? "YES" : "NO");
}

// Helper function to print entire command list
void print_all_commands(t_stack *cmd_list)
{
    t_cmds *cmd;
    int i;

    if (!cmd_list || !cmd_list->head)
    {
        printf("\n⚠️  Empty command list\n");
        return;
    }

    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║       PARSED COMMAND STRUCTURE            ║\n");
    printf("╚════════════════════════════════════════════╝\n");

    cmd = cmd_list->head;
    i = 0;
    while (cmd)
    {
        print_command(cmd, i);
        cmd = cmd->next;
        i++;
    }
    
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  Total commands: %d\n", cmd_list->size);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("\n");
}

int main(void)
{
    t_stack         *cmd_list;
    t_token_list    *tokens;
    char            *input;

    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║     MINISHELL PARSER TEST                 ║\n");
    printf("║     (Ctrl+D to exit)                      ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\n");

    while (1)
    {
        // Read input
        input = readline("minishell> ");
        
        // Handle EOF (Ctrl+D)
        if (!input)
        {
            printf("\nexit\n");
            break;
        }
        
        // Skip empty input
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        // Add to history
        add_history(input);
        
        // ================================================================
        // LEXER: Tokenize input
        // ================================================================
        tokens = tokenizer(input);
        if (!tokens)
        {
            fprintf(stderr, "❌ Error: Tokenization failed\n");
            free(input);
            continue;
        }
        
        if (!tokens->head)
        {
            fprintf(stderr, "⚠️  Warning: No tokens generated\n");
            free_token_list(tokens);
            free(input);
            continue;
        }
        
        // ================================================================
        // PARSER: Build command structure
        // ================================================================
        cmd_list = parsing(tokens);
        if (!cmd_list)
        {
            fprintf(stderr, "❌ Error: Parsing failed\n");
            free_token_list(tokens);
            free(input);
            continue;
        }
        
        // ================================================================
        // DEBUG: Print parsed structure
        // ================================================================
        print_all_commands(cmd_list);
        
        // ================================================================
        // CLEANUP: Free everything
        // ================================================================
        free_cmd_list(cmd_list);
        free_token_list(tokens);
        free(input);
    }
    
    return (0);
}