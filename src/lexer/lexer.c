/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:50 by abita             #+#    #+#             */
/*   Updated: 2026/01/24 15:05:26 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_check(const char *line, int *i, t_token *tok)
{
	if (decide_token_type((char *)line, i, tok) != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	if (tok->typ == TOKEN_WORD)
	{
		if (collect_word_content((char *)line, i, tok) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (set_operator_content(tok) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	lexer_loop(const char *line, t_token_list *lst, t_token	*tok)
{
	int				i;

	i = 0;
	while (line && line[i])
	{
		i = skip_whitespace((char *)line, i);
		if (!line[i])
			break ;
		tok = create_token();
		if (!tok)
			return (cleanup_all(lst, NULL), EXIT_FAILURE);
		if (token_check(line, &i, tok) != EXIT_SUCCESS)
			return (cleanup_all(lst, tok), EXIT_FAILURE);
		if (add_token(lst, tok) != EXIT_SUCCESS)
			return (cleanup_all(lst, tok), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_token_list	*tokenizer(const char *line)
{
	t_token_list	*lst;
	t_token			*tok;

	tok = NULL;
	lst = init_token_list();
	if (!lst)
		return (NULL);
	if (lexer_loop(line, lst, tok) == EXIT_SUCCESS)
		return (lst);
	return (NULL);
}
