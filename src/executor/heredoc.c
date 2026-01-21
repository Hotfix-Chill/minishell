/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 02:34:22 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/21 18:22:31 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_into_heredoc(t_data *data, t_redirs *redirs, int fd)
{
	char			*line;
	char			*delimiter;
	int				delimiter_len;
	static size_t	count = 0;
	char			*new_line;

	delimiter = redirs->filename;
	delimiter_len = ft_strlen(delimiter);
	init_signals_heredoc();
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		count++;
		if ((!line))
		{
			printf("minishell: warning: here-document at line %li delimited " \
				"by end-of-file (wanted `%s')\n", count, redirs->filename);
			return (0);
		}
		if (!ft_memcmp(line, delimiter, delimiter_len + 1) || g_signal == 1)
			return (free(line), 0);
		if (redirs->heredoc_expand && find_char(line, '$') != NO_DOLLAR)
		{
			new_line = split_dollar(data, line);
			free(line);
			write(fd, new_line, ft_strlen(new_line));
			write(fd, "\n", 1);
			free(new_line);
		}
		else {
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
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

/* static char	*get_filename(int index)
{
	int pid_nb;
	char *tmp;
	char *nb;
	char *pid;
	char *filename;

	pid_nb = getpid();
	pid = ft_itoa(pid_nb);
	if (!pid)
		return (NULL);
	nb = ft_itoa(index);
	if (!nb)
		return (free(pid), NULL);
	tmp = ft_strjoin(pid, nb);
	free(pid);
	free(nb);
	if (!tmp)
		return(NULL);
	filename = ft_strjoin("heredoc_", tmp);
	free(tmp);
	if (!filename)
		return (NULL);
	return (filename);
} */

// creates a file with random name from name + pid + index
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

// finds heredocs by heredoc flag if true!
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
