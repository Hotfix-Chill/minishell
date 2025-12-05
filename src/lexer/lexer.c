/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:50 by abita             #+#    #+#             */
/*   Updated: 2025/11/19 15:43:52 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	A parser is divided into two parts: a Lexical Analyzer or Lexer takes the input characters and
puts the characters together into words called tokens,
	and a Parser that processes the
tokens according to a grammar and build the command table.

*/

static int	append_char_to_content(t_token *toklist, char c)
{
	char	*new_content;
	char	*old_content;
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	if (toklist->content == NULL)
		new_content = ft_strdup(char_str);
	else
	{
		old_content = toklist->content;
		new_content = ft_strjoin(old_content, char_str);
		// if not null join the existing str
	}
	if (!new_content)
		return (-1);      // ALLOCATION_FAILED create an enum to clean up
	if (toklist->content) // here i free the old contetn and update the pointer
		free(toklist->content);
	toklist->content = new_content;
	return (EXIT_SUCCESS);
}

static int	collect_word_content(char *line, int *i_ptr, t_token *tok)
{
	int		i;
	char	c;
	int		prev_quote;

	i = *i_ptr;
	tok->quote = QUOTE_NORMAL;
	while (line[i])
	{
		// check if we hit a boundary (space, pipe, redir, eof)
		c = line[i];
		if (tok->quote == QUOTE_NORMAL)
		{
			if (c == '\'')
			{
				tok->quote = QUOTE_SINGLE;
				i++;
				continue ;
			}
			if (c == '"')
			{
				tok->quote = QUOTE_DOUBLE;
				i++;
				continue ;
			}
			if (c == '|' || c == '<' || c == '>' || ft_isspace(c))
				break ;
			if (append_char_to_content(tok, c) < 0)
				return (-1);
			i++;
		}
		else if (tok->quote == QUOTE_DOUBLE)
		{
			if (c == '\'')
			{
				tok->quote = QUOTE_NORMAL;
				i++;
				continue ;
			}
			if (append_char_to_content(tok, c) < 0)
				return (-1);
			i++;
		}
		else if (tok->quote == QUOTE_DOUBLE)
		{
			if (c == '"')
			{
				tok->quote = QUOTE_NORMAL;
				i++;
				continue ;
			}
			if (append_char_to_content(tok, c) < 0)
				return (-1);
			i++;
		}
	}
	if (tok->quote != QUOTE_NORMAL)
		return (-1); // unmatched quote error
	*i_ptr = i;
	return (EXIT_SUCCESS);
}

static int	decide_token_type(char *line, int *i_ptr, t_token *tok)
{
	int		i;
	char	c;
	char	next_c;

	i = *i_ptr;
	c = line[i];
	next_c = line[i + 1];
	if (c == '|')
		return (tok->typ = TOKEN_PIPE, *i_ptr = i + 1, EXIT_SUCCESS);
	else if (c == '>' && next_c == '>')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_APPEND, *i_ptr = i
			+ 2, EXIT_SUCCESS);
	else if (c == '<' && next_c == '<')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_HEREDOC, *i_ptr = i
			+ 2, EXIT_SUCCESS);
	else if (c == '>')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_OUT, *i_ptr = i + 1,
			EXIT_SUCCESS);
	else if (c == '<')
		return (tok->typ = TOKEN_REDIR, tok->redir = REDIR_IN, *i_ptr = i + 1,
			EXIT_SUCCESS);
	tok->typ = TOKEN_WORD;
	tok->quote = QUOTE_NORMAL;
	return (0);
}
// Lexer allocates every t_token node and each content string.
// return head of list if success or NULL in case of error
t_token	*tokenizer(const char *line)
{
	int				i;
	t_token			*tok;
	t_token_list	*lst;

	i = 0;
	lst = init_token_list();
	if (!lst)
		return (NULL);
	// toklist->quote = QUOTE_NORMAL;
	while (line && line[i])
	{
		// a funct that advances i for each iter and checks for whitespaces
		i = skip_whitespace(line, i);
		// check if we hit the null term after skipping spaces
		if (!line[i])
			break ;
		tok = create_token;
		if (!tok)
			return (free_token_list(lst), NULL);
		// token definition function
		decide_token_type((char *)line, &i, tok);
		if (tok->typ == TOKEN_WORD)
		{
			if (collect_word_content(line, &i, tok) != EXIT_SUCCESS)
				return (free(tok->content), free(tok), free_token_list(lst), NULL);
		}
		else
		{
			if (tok->typ == TOKEN_PIPE)
				append_str_to_content(tok, "|");
			else if (tok->typ == TOKEN_REDIR)
			{
				if (tok->redir == REDIR_APPEND)
					append_str_to_content(tok, ">>");
				else if (tok->redir == REDIR_HEREDOC)
					append_str_to_content(tok, "<<");
				else if (tok->redir == REDIR_IN)
					append_str_to_content(tok, "<");
				else if (tok->redir == REDIR_OUT)
					append_str_to_content(tok, ">");
			}
		}
		if (add_token(lst, tok) != EXIT_SUCCESS)
			return (free_token_list(lst), free(tok->content), free(tok), NULL);
	}
	return (lst);
}


// /* test_main.c */
// #include <stdio.h>
// #include <stdlib.h>

// /* print helper */
// const char *type_name(t_token *t)
// {
//     if (!t) return "NULL";
//     if (t->typ == TOKEN_WORD) return "WORD";
//     if (t->typ == TOKEN_PIPE) return "PIPE";
//     if (t->typ == TOKEN_REDIR) return "REDIR";
//     return "UNK";
// }

// void print_tokens_list(t_token_list *lst)
// {
//     t_token *cur = lst->head;
//     int idx = 0;
//     while (cur)
//     {
//         printf("[%02d] %s (%s) : '%s'\n", idx++,
//                type_name(cur),
//                (cur->redir==REDIR_NONE?"-":
//                 cur->redir==REDIR_IN?"IN":
//                 cur->redir==REDIR_OUT?"OUT":
//                 cur->redir==REDIR_APPEND?"APPEND":"HEREDOC"),
//                cur->content ? cur->content : "");
//         cur = cur->next;
//     }
// }

// /* provide or link tokenizer, free_token_list */
// int main(void)
// {
//     char *line = NULL;
//     size_t cap = 0;
//     ssize_t n;
//     printf("Enter lines (Ctrl+D to quit):\n> ");
//     while ((n = getline(&line, &cap, stdin)) > 0)
//     {
//         if (line[n-1] == '\n') line[n-1] = '\0';
//         t_token_list *lst = tokenizer(line);
//         if (!lst) fprintf(stderr, "tokenizer error\n");
//         else
//         {
//             print_tokens_list(lst);
//             free_token_list(lst);
//         }
//         printf("> ");
//     }
//     free(line);
//     return 0;
// }
