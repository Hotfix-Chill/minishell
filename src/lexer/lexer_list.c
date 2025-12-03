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

t_token_list *create_node(char *line)
{
	t_token_list *list;

	list = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->head = line;
	list->tail = NULL;
	list->size = NULL;
	return (list);
}

// insert the node at the beggining
// void insert_beginning(t_token_list **head, char *line)
// {
// 	t_token_list *list;

// 	list = create_node(line);
// 	if (*head == NULL)
// 	{
// 		*head = list;
// 		return ;
// 	}
// 	list->next = *head;
// 	(*head)->prev = list;
// 	*head = list; 
// }

// insert a node in the end
void insert_end(t_token **head, char *line)
{
	t_token *new_token;
	t_token *tmp;

	new_token = create_node(line);
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
}