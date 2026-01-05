/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 05:08:17 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define CMD 0			//for t_cmds struct
# define ARGS 1			//for t_cmds struct

#define ERROR 1
#define OK_EXIT 0
#define RESET 424242

# ifndef DEBUG_ALLOC
#  define DEBUG_ALLOC 0
# endif

# define PWD 0
# define SHLVL 1
# define LAST_CMD 2

// # define TOKEN_REDIR_IN 0
// # define TOKEN_REDIR_OUT 1
// # define TOKEN_REDIR_APPEND 2
// # define TOKEN_REDIR_HEREDOC 3
// # define TOKEN_PIPE 4
// # define TOKEN_WORD 5

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

// FREE
// data->env ------> free_split  		**char of environment variables**
// data->path_list  -----> free_split 	**for PATH variable split by ':'**
// data->redirs -----> free_redirs		**linked list of redirections
// rdirs->filename -----> free()		**filename or delimiter string**
// data->cmd ------> free_cmds			**linked list of commands**
// data->cmd->argv -----> free_split	**array of command and arguments**
// data->exec.heredoc_files				**array of tmp heredoc_filenames

# define 	REDIR_NOT_FOUND  0
# define 	REDIR_ERROR  -1
# define 	REDIR_FOUND  1	 // a check that lets me know i found a redir


// LEXER //
typedef enum e_redir_type
{
    REDIR_NONE = 0,
	REDIR_IN,        // <
    REDIR_OUT,       // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC,   // <<
}   t_redir_type;


typedef enum e_token_type
{
	TOKEN_WORD = 0, // words
	TOKEN_PIPE, // pipes
	TOKEN_REDIR
} t_token_type;


typedef enum e_quote_type
{
	QUOTE_NORMAL = 0,  // outside any quote
	QUOTE_SINGLE,  // inside '  '
	QUOTE_DOUBLE   // inside "   "
} t_quote_type;



// DS: Double - Linked list
typedef struct s_token
{
	t_token_type	typ;	  // main token type
	t_redir_type	redir;	  // valid if typ == TOKEN_REDIR
	char			*content; // allocated str; can be NULL
	int 			len;	  // current len of the content
	int 			cap;	  // allowed capacity
	t_quote_type	quote;	  // where the token came from
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_token_list
{
	t_token *head;
	t_token *tail;
	int 	size;
}	t_token_list;
//////////////////////////////////////////// Lexer END


typedef struct flag
{
	bool	shlvl;
	bool	pwd;
	bool	last_cmd;
	bool	redirect_fail;
	bool	abort;				// for heredoc interruption

}	t_flag;



typedef struct fildescriptor
{
	int	curr[2];
	int	prev[2];
}	t_fds;

///////// PARSER //////////////////////

typedef struct redirections
{
	t_redir_type		typ;
	char				*filename;
	bool				heredoc;	// ARESLA needs to set the flag! if REDIR_HEREDOC/ TOKEN_HERDOC
	struct redirections	*next;
}	t_redirs;


typedef struct cmds
{
	char		**argv;
	t_redirs	*redirs;
	bool		pipe_after;			// ARESLA needs to set the flag! is there a pipe comming after cmd? last cmd has no pipe after, always false
	struct cmds	*next;
}	t_cmds;


typedef struct list
{
	int		size;			//ARESELA has to count each t_cmds node with data->list.size++;
	t_cmds	*head;
	t_cmds	*tail;
}	t_stack;

/////////////////////////////////////////////

typedef struct heredocs
{
	char	**files; 	// array of heredoc filenames to be unlinked at the end
	int		count;		// ARSLEA needs to count up in parsing heredoc_count++ // number of heredoc files created
	int		index;
}	t_heredoc;



typedef struct execute
{
	char	**search_paths;
	char	*path;
}	t_exec;


typedef struct s_data
{
	char		*tmp;
	char		**path_list;
	char		*user;
	char		**env;
	uint		return_value;		// handle in expander for echo $?

	t_fds		fd;
	t_exec		exec;
	t_cmds		*cmd;
	t_stack		list;
	t_flag		flag;
	t_heredoc	heredoc;
}	t_data;





// GLOBAL VAR
extern volatile sig_atomic_t g_signal;




// START
bool	init_env(char **envp, t_data *data);
void	cleanup(t_data *data, int exit_code);
char	*ft_extract_digits(char const *str);



///////////////////////////////////////////////////////////
// LEXER //

// main tokenizer flow
t_token_list	*tokenizer(const char *line);


// lexer append funct to build the content (content manipulation)
int	append_char_to_content(t_token *tok, char c);
int append_str_to_content(t_token *tok, char *str);
int	collect_word_content(char *line, int *i_ptr, t_token *tok);

// creating adding list
t_token_list *init_token_list(void);
t_token *create_token(void);
int add_token(t_token_list *lst, t_token *node);
void free_token_list(t_token_list *lst);


// lexer quote state
int handle_quote_char(t_token *tok, char c);


// character validation
int	skip_whitespace(char *line, int i);
bool is_metachar(char c);
bool should_break_word(char c, t_quote_type quote);

// quote handling
bool is_quote(char c);
bool is_closing_quote(char c, t_quote_type quote);

// lexer cleanup
void *cleanup_token(t_token *tok);
void *cleanup_all(t_token_list *lst, t_token *tok);
///////////////////////////////////////////////////////////// END OF LEXER

/// Parser /// 

// parser_cmd
t_stack *init_cmd_list(void);
t_cmds *create_cmds(void);
int add_cmd_to_list(t_stack *lst, t_cmds *node);
int add_arg_to_cmd(t_cmds *curr_cmd, const char *tok_content);
void free_cmd_list(t_stack *lst);

// parser redir
int add_redir_to_cmd(t_cmds *cmd, t_token *redir_token, t_token *filename_token);
t_redirs *init_redir(void);

// main parser
t_stack *parsing(t_token_list *token);


///////////////////////////////////////////////////////////// END OF PARSER

//EXECUTION
void	single_cmd(t_data *data, t_cmds *cmd);
void	handle_errno(t_data *data, t_cmds *cmd, int error_code);
void	child_cleanup(int exit_code, char *message, t_data *data, t_cmds *cmd);
void	handle_redirections(t_data *data, t_cmds *cmd);
void	executor(t_cmds *cmd, t_data *data); ////DELETE LATER, JUST DEBUG
void	multi_cmds(t_data *data, t_cmds *cmd);
// void	executor(char *line, t_data *data); // FINAL one
void	ft_close(t_data *data);
void	get_exit_status(t_data *data, int pid);
void	exec_cmd(t_data *data, t_cmds *cmd);
int		heredocs(t_data *data, t_cmds *cmd);



//CLEANUP
void free_token_list(t_token_list *lst);



void    free_split(char **split);
void    redirs_lstclear(t_redirs **lst);
void    cmd_lstclear(t_cmds **lst);
void	reset_readline(t_data *data);


//SIGNALS
void	prompt_handler(int sig);
void	*init_signals_prompt(void);
void	heredoc_handler(int sig);
void	init_signals_heredoc(void);


//VERBOSE
void	print_env(t_data *data);
void	init_single_command_struct(t_data *data);
void	*debug_build_commands(t_data *data);
void	print_cmd_list(t_cmds *head);



#endif
