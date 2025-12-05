/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:48:09 by abita             #+#    #+#             */
/*   Updated: 2025/12/02 20:48:11 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token_list *init_token_list(void)
{
	t_token_list *lst;

	lst = (t_token_list *)ft_calloc(1, sizeof(*lst));
	if (!lst)
		return (NULL);
}

t_token *create_token(void)
{
	t_token *token;

	token = (t_token*)ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->typ = TOKEN_WORD;
	token->redir = REDIR_NONE;
	token->content = NULL;
	token->len = 0;
	token->cap = 0;
	token->quote = QUOTE_NORMAL;
	token->next = token->prev = NULL; 
	return (token);
}
int add_token(t_token_list *lst, t_token *node)
{
	if (!lst || !node)
		return (-1);
	if (!lst->head)
		lst->head = lst->tail = node;
	else
	{
		lst->tail->next = node;
		node->prev = lst->tail;
		lst->tail = node;
	}
	lst->size++;
	return (EXIT_SUCCESS);
}

void free_token_list(t_token_list *lst)
{
	t_token *cur;
	t_token *next;

	if (!lst)
		return ;
	cur = lst->head;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	free(lst);
}