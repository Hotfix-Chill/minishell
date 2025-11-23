/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/21 18:08:46 by pjelinek         ###   ########.fr       */
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

# define PWD 0
# define SHLVL 1
# define LAST_CMD 2

# define TOKEN_REDIR_IN 0
# define TOKEN_REDIR_OUT 1
# define TOKEN_REDIR_APPEND 2
# define TOKEN_REDIR_HEREDOC 3
# define TOKEN_PIPE 4
# define TOKEN_WORD 5

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"



typedef enum e_redir_type
{
    REDIR_IN,        // <
    REDIR_OUT,       // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC    // <<
}   t_redir_type;



typedef struct Token
{
	int 			typ;  //WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char			*content; //string, "ls", "-l", "out.txt"
	struct Token	*next;
}	t_token;



typedef struct flag
{
	bool	shlvl;
	bool	pwd;
	bool	last_cmd;
	bool	redirect;

}	t_flag;

typedef struct fildescriptor
{
	int	input;
	int	output;
	int	curr[2];
	int	prev[2];
}	t_fds;

typedef struct redirections
{
	int					typ;		// REDIR_IN, REDIR_OUT, REDIR_APPEND
	char				*filename;	//filename or heredoc delimiter
	struct redirections	*next;
}	t_redirs;


typedef struct cmds
{
	char		**argv;			//cmd_line[0] == cmd; cmd_line[1] == args; -> NULL
	t_redirs	*redirs;


	char		*redir_type;	// DELETR LATER   < > >> etc or NULL;
	char		*redir_target;	// DELETE LATER filenames ex: doc.txt or NULL;

	bool		pipe_after;		// is there a pipe or end of commands --> NULL
	struct cmds	*next;
}	t_cmds;

typedef struct list
{
	int		size;
	t_cmds	*head;
	t_cmds	*tail;
}	t_stack;

typedef struct execute
{
	char	**search_paths;
	char	*path;

}	t_exec;

typedef struct s_data
{
	char	*tmp;
	char	**path_list;
	char	*user;
	char	**env;

	uint	return_value;		// handle in expander for echo $?

	t_exec	exec;
	t_cmds	*cmd;
	t_stack	list;
	t_flag	flag;
}	t_data;

// START
bool	init_env(char **envp, t_data *data);
void	cleanup(t_data *data);
char	*ft_extract_digits(char const *str);





//LEXER



//PARSER





//EXECUTION
void	single_cmd(t_data *data, t_cmds *cmd);
void	handle_errno(t_data *data, t_cmds *cmd, int error_code);
void	child_cleanup(int exit_code, char *message, t_data *data, t_cmds *cmd);
void	handle_redirections(t_data *data, t_cmds *cmd);
void	debug_executor(t_cmds *cmd, t_data *data); ////DELETE LATER, JUST DEBUG
//void	executor(char *line, t_data *data); // FINAL one





//VERBOSE
void	print_env(t_data *data);
void	init_single_command_struct(t_data *data);

#endif
