/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:39:56 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/16 08:44:27 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                CONFIG / MACROS                             */
/* ************************************************************************** */

# define _DEFAULT_SOURCE

# ifndef VERBOSE
#  define VERBOSE 0
# endif

/* indices / magic values */
# define CMD 0
# define ARGS 1

# define ERROR 1
# define OK_EXIT 0
# define RESET 424242
# define EQUAL_VS_NULL_TERM 61
# define HEREDOC_PROMPT "> "
# define NOT_FOUND_DOLLAR -1

/* redir status helpers */
# define REDIR_NOT_FOUND 0
# define REDIR_ERROR -1
# define REDIR_FOUND 1

/* env indices (if you rely on fixed slots) */
# define PWD 0
# define SHLVL 1
# define LAST_CMD 2

/* ************************************************************************** */
/*                                   INCLUDES                                 */
/* ************************************************************************** */

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
# include <signal.h>
# include <sys/ioctl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

/* ************************************************************************** */
/*                                   TYPES                                    */
/* ************************************************************************** */

typedef enum e_redir_type
{
	REDIR_NONE = 0,
	REDIR_IN,        /* <  */
	REDIR_OUT,       /* >  */
	REDIR_APPEND,    /* >> */
	REDIR_HEREDOC    /* << */
}	t_redir_type;

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_REDIR
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NORMAL = 0, /* outside quotes */
	QUOTE_SINGLE,     /* inside '...'   */
	QUOTE_DOUBLE      /* inside "..."   */
}	t_quote_type;

/* ************************************************************************** */
/*                                 LEXER / TOKENS                             */
/* ************************************************************************** */

typedef struct s_token
{
	t_token_type		typ;       /* main token type */
	char				*content;  /* allocated string; can be NULL */
	int					redir;
	int					len;       /* current length */
	int					cap;       /* allocated capacity */
	t_quote_type		quote;     /* quote context */
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	int		size;
}	t_token_list;

/* ************************************************************************** */
/*                               PARSER / COMMANDS                            */
/* ************************************************************************** */

typedef struct s_redirections
{
	t_redir_type			typ;
	char					*filename;
	bool					heredoc; /* set true when typ == REDIR_HEREDOC */
	struct s_redirections	*next;
}	t_redirs;

typedef struct s_cmds
{
	char			**argv;
	t_redirs		*redirs;
	bool			builtin;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_stack
{
	int		size;
	t_cmds	*head;
	t_cmds	*tail;
}	t_stack;

/* ************************************************************************** */
/*                                 EXECUTION / IO                             */
/* ************************************************************************** */

typedef struct s_fds
{
	int	curr[2];
	int	prev[2];
}	t_fds;

typedef struct s_exec
{
	char	**search_paths;
	char	*path;
}	t_exec;

/* ************************************************************************** */
/*                                  ENV / EXPORT                              */
/* ************************************************************************** */

typedef struct s_export
{
	char	*key;
	char	*value;
	bool	flag;
}	t_export;

typedef struct s_flag
{
	bool	shlvl;
	bool	pwd;
	bool	last_cmd;
	bool	redirect_fail;
	bool	equal_exists;
}	t_flag;

/* ************************************************************************** */
/*                                   HEREDOC                                  */
/* ************************************************************************** */

typedef struct s_heredoc
{
	char	**files;  /* filenames to unlink at the end */
	int		count;   /* number of heredoc files created */
	int		index;
}	t_heredoc;

/* ************************************************************************** */
/*                                   GLOBAL DATA                              */
/* ************************************************************************** */

typedef struct s_data
{
	char			*tmp;

	char			**path_list;
	char			**env;
	char			*pwd;

	size_t			env_len;
	size_t			export_len;

	unsigned int	return_value; /* for $? */

	t_fds			fd;
	t_exec			exec;
	t_cmds			*cmd;
	t_stack			*list;
	t_flag			flag;
	t_export		*export;
	t_heredoc		heredoc;
}	t_data;

/* ************************************************************************** */
/*                               GLOBAL VARIABLE                              */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_signal;

/* ************************************************************************** */
/*                                 START / CORE                               */
/* ************************************************************************** */

bool		init_env(char **envp, t_data *data);
char		*increment_shlvl(char *str);
void		cleanup(t_data *data, int exit_code);
char		*ft_extract_digits(char const *str);
bool		split_into_key_and_value(t_data *data, char *str, int idx);

/* ************************************************************************** */
/*                                   EXECUTION                                */
/* ************************************************************************** */

void		single_cmd(t_data *data, t_cmds *cmd);
void		multi_cmds(t_data *data, t_cmds *cmd);
void		executor(t_cmds *cmd, t_data *data);

void		exec_cmd(t_data *data, t_cmds *cmd);
void		handle_errno(t_data *data, t_cmds *cmd, int error_code);
void		child_cleanup(
	int exit_code, char *message, t_data *data, t_cmds *cmd
);

void		handle_redirections(t_data *data, t_cmds *cmd);
int			heredocs(t_data *data, t_cmds *cmd);

void		ft_close(t_data *data);
void		get_exit_status(t_data *data, int pid);
void		print_exit_signals(int status);

char		**get_path_list(t_data *data, t_cmds *cmd);

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

bool		exec_builtins(t_data *data, t_cmds *cmd);
void		ft_pwd(t_data *data);
void		ft_env(t_data *data, t_cmds *cmd);
void		ft_echo(t_data *data, t_cmds *cmd);
void		ft_exit(t_data *data, t_cmds *cmd);
void		ft_unset(t_data *data, t_cmds *cmd);
void		ft_cd(t_data *data, t_cmds *cmd);
void		ft_export(t_data *data, t_cmds *cmd);

/* ************************************************************************** */
/*                                ENV & EXPORT LISTS                          */
/* ************************************************************************** */

void		add_env_entry(t_data *data, char *str, char *key);
bool		add_export_entry(t_data *data, char *key, char *value);

char		*get_key(char *str, t_data *data);
char		*get_value(t_data *data, char *str, char *key);

bool		check_entry_export(t_data *data, char *key, char *value);
bool		check_entry_env(t_data *data, char *key, char *str);

char		**ft_realloc_env(t_data *data, char **env, size_t len, int min);
t_export	*ft_realloc_export(
	t_data *data, t_export *export, size_t size, int min
);

int			find_char(char *str, char c);


/* ************************************************************************** */
/*                                     CLEANUP                                */
/* ************************************************************************** */

void		free_split(char **split);
void		redirs_lstclear(t_redirs **lst);
void		cmd_lstclear(t_cmds **lst);
void		clean_export(t_export *export, size_t size);

/* ************************************************************************** */
/*                                     SIGNALS                                */
/* ************************************************************************** */

void		prompt_handler(int sig);
void		*init_signals_prompt(void);
void		heredoc_handler(int sig);
void		init_signals_heredoc(void);
void		init_signals_parent(void);
void		init_signals_child(void);

/* ************************************************************************** */
/*                                     DEBUG / VERBOSE                        */
/* ************************************************************************** */

void		print_env(t_data *data);
void		init_single_command_struct(t_data *data);
void		*debug_build_commands(t_data *data);
void		print_cmd_list(t_cmds *head);
void		print_token_list(t_token_list *tokens);

/* ************************************************************************** */
/*                                      LEXER                                 */
/* ************************************************************************** */

/* main */
t_token_list	*tokenizer(const char *line);

/* token content building */
int			append_char_to_content(t_token *tok, char c);
int			append_str_to_content(t_token *tok, char *str);
int			collect_word_content(char *line, int *i_ptr, t_token *tok);

/* operators */
int			redir_check(char *line, int *i_ptr, t_token *tok);
int			pipe_check(char *line, int *i_ptr, t_token *tok);
int			decide_token_type(char *line, int *i_ptr, t_token *tok);
int			set_operator_content(t_token *tok);

/* list creation */
t_token_list	*init_token_list(void);
t_token			*create_token(void);
int			add_token(t_token_list *lst, t_token *node);

/* quote state */
int			handle_quote_char(t_token *tok, char c);

/* character validation */
int			skip_whitespace(char *line, int i);
bool		is_metachar(char c);
bool		should_break_word(char c, t_quote_type quote);

/* quote handling helpers */
bool		is_quote(char c);
bool		is_closing_quote(char c, t_quote_type quote);

/* lexer cleanup */
void		free_token_list(t_token_list *lst);
void		*cleanup_token(t_token *tok);
void		*cleanup_all(t_token_list *lst, t_token *tok);

/* ************************************************************************** */
/*                                      PARSER                                */
/* ************************************************************************** */

/* parser_cmd */
t_stack		*init_cmd_list(void);
t_cmds		*create_cmds(void);
int			add_cmd_to_list(t_stack *lst, t_cmds *node);
int			add_arg_to_cmd(t_cmds *curr_cmd, const char *tok_content);
void		free_cmds(t_cmds *cmd);
void		free_cmd_list(t_stack *lst);

/* parser redir */
t_redirs		*init_redir(void);
int			add_redir_to_cmd(t_cmds *cmd, t_token *redir_token,
				t_token *filename_token, t_data *data);

/* main parser */
t_stack		*parsing(t_token_list *token, t_data *data);

/* ************************************************************************** */
/*                                     EXPANDER                               */
/* ************************************************************************** */

int			expansion(t_stack *cmd_list, t_data *data);
char	 	*extract_var(t_data *data, char *extract_var);
char		*split_dollar(t_data *data, char *str);

#endif
