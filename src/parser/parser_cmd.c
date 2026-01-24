/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:32:39 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 00:06:33 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void copy_old_args(t_cmds *curr_cmd, t_argbuff *buf, int arg_count)
{
	int i;

	i = 0;
	while (i < arg_count)
	{
		buf->new_argv[i] = curr_cmd->argv[i];
		if (curr_cmd->no_expand)
			buf->flag_for_expansion[i] = curr_cmd->no_expand[i];
		else
			buf->flag_for_expansion[i] = false;
		if (curr_cmd->no_split)
			buf->flag_for_split[i] = curr_cmd->no_split[i];
		else
			buf->flag_for_split[i] = false;
		i++;
	}
}

static int alloc_argbuff(t_cmds *curr_cmd, t_argbuff *buf)
{
	int arg_count;

	arg_count = count(curr_cmd);
	buf->new_argv = (char **)ft_calloc(arg_count + 2, sizeof(char *));
	if (!buf->new_argv)
		return (-1);
	buf->flag_for_expansion = (bool *)ft_calloc(arg_count + 2, sizeof(bool));
	if (!buf->flag_for_expansion)
		return (free (buf->new_argv), -1);
	buf->flag_for_split = (bool *)ft_calloc(arg_count + 2, sizeof(bool));
	if (!buf->flag_for_split)
			return (free(buf->new_argv), free(buf->flag_for_expansion), -1);
	return (arg_count);
}

int add_arg_to_cmd(t_cmds *curr_cmd, const char *tok_content,
	bool no_expand_flag, bool no_split_flag)
{
	int 	arg_count;
	t_argbuff buf;

	if (!curr_cmd || !tok_content)
		return (-1);
	arg_count = alloc_argbuff(curr_cmd, &buf);
	if (arg_count < 0)
		return (-1);
	copy_old_args(curr_cmd, &buf, arg_count);
	buf.new_argv[arg_count] = ft_strdup(tok_content);
	if (!buf.new_argv[arg_count])
		return (free(buf.new_argv), free(buf.flag_for_expansion), free(buf.flag_for_split), -1);
	buf.flag_for_expansion[arg_count] = no_expand_flag;
	buf.flag_for_split[arg_count] = no_split_flag;
	buf.new_argv[arg_count + 1] = NULL;
	free(curr_cmd->no_expand);
	free(curr_cmd->argv);
	free(curr_cmd->no_split);
	curr_cmd->argv = buf.new_argv;
	curr_cmd->no_expand = buf.flag_for_expansion;
	curr_cmd->no_split = buf.flag_for_split;
	return (EXIT_SUCCESS);
}
