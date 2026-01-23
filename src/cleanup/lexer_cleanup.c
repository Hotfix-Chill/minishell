/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:43:05 by abita             #+#    #+#             */
/*   Updated: 2026/01/23 16:21:54 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*cleanup_token(t_token *tok)
{
	if (tok)
	{
		free(tok->content);
		free(tok);
	}
	return (NULL);
}

void	*cleanup_all(t_token_list *lst, t_token *tok)
{
	cleanup_token(tok);
	free_token_list(lst);
	return (NULL);
}
