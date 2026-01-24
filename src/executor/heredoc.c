/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 02:34:22 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 14:23:12 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_heredoc_sigquit(char *redirs_filename, size_t line_count)
{
	printf("minishell: warning: here-document at line %li delimited " \
		"by end-of-file (wanted `%s')\n", line_count, redirs_filename);
	return ;
}

static int	write_into_heredoc(t_data *data, t_redirs *redirs, int fd)
{
	char			*line;
	char			*delimiter;
	int				delimiter_len;
	static size_t	count = 0;

	delimiter = redirs->filename;
	delimiter_len = ft_strlen(delimiter);
	init_signals_heredoc();
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		count++;
		if ((!line))
		{
			print_heredoc_sigquit(redirs->filename, count);
			return (0);
		}
		if (!ft_memcmp(line, delimiter, delimiter_len + 1) || g_signal == 1)
			return (free(line), 0);
		if (redirs->heredoc_expand && find_char(line, '$') != NO_DOLLAR)
			heredoc_expand(data, line, fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

static char	*get_filename(int index)
{
	char	*idx;
	char	*filename;

	idx = ft_itoa(index);
	if (!idx)
		return (NULL);
	filename = ft_strjoin("heredoc_", idx);
	free(idx);
	if (!filename)
		return (NULL);
	return (filename);
}

static void	create_file(t_data *data, t_redirs *redir)
{
	int		fd;
	char	*heredoc_name;
	int		index;

	fd = -1;
	if (!redir)
		return ;
	index = data->heredoc.index;
	heredoc_name = get_filename(index);
	data->heredoc.files[index] = ft_strdup(heredoc_name);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || !heredoc_name || !data->heredoc.files[index])
	{
		if (fd >= 0)
			close(fd);
		cleanup(data, ERROR);
	}
	write_into_heredoc(data, redir, fd);
	free(redir->filename);
	redir->filename = NULL;
	redir->typ = REDIR_IN;
	redir->filename = heredoc_name;
	data->heredoc.index++;
	if (fd >= 0)
		close(fd);
}

int	heredocs(t_data *data, t_cmds *cmd)
{
	t_cmds		*curr;
	t_redirs	*redirs;

	data->heredoc.files = ft_calloc(data->heredoc.count + 1, sizeof(char *));
	if (!data->heredoc.files)
		cleanup(data, ERROR);
	curr = cmd;
	while (curr)
	{
		redirs = curr->redirs;
		while (redirs)
		{
			if (redirs->heredoc == true && g_signal == 0)
				create_file(data, redirs);
			redirs = redirs->next;
		}
		curr = curr->next;
	}
	init_signals_prompt();
	if (g_signal == 1)
	{
		cleanup(data, RESET);
		return (SIGINT);
	}
	return (0);
}
