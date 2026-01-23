/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:44:31 by abita             #+#    #+#             */
/*   Updated: 2026/01/21 12:54:19 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirs	*init_redir(void)
{
	t_redirs	*redirs;

	redirs = (t_redirs *)ft_calloc(1, sizeof(*redirs));
	if (!redirs)
		return (NULL);
	redirs->filename = NULL;
	redirs->heredoc = false;
	redirs->next = NULL;
	return (redirs);
}

int	add_redir_to_cmd(t_cmds *cmd, t_token *redir_token, \
	t_token *filename_token, t_data *data)
{
	t_redirs	*new_redirs;
	t_redirs	*last;

	if (!cmd || !redir_token || !filename_token)
		return (-1);
	new_redirs = init_redir();
	if (!new_redirs)
		return (-1);
	new_redirs->typ = redir_token->redir;
	new_redirs->filename = ft_strdup(filename_token->content);
	new_redirs->no_expand = filename_token->no_expand;
	if (!new_redirs->filename)
		return (free(new_redirs), -1);
	if (new_redirs->typ == REDIR_HEREDOC)
	{
		new_redirs->heredoc = true;
		data->heredoc.count++;
		if (filename_token->quoted)
			new_redirs->heredoc_expand = false;
		else
			new_redirs->heredoc_expand = true;
	}
	if (!cmd->redirs)
		cmd->redirs = new_redirs;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redirs;
	}
	return (EXIT_SUCCESS);
}
