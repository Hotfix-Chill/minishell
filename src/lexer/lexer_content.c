/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:50:58 by abita             #+#    #+#             */
/*   Updated: 2026/01/21 12:55:14 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char_to_content(t_token *tok, char c)
{
	char	*new_content;
	char	*old_content;
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	if (tok->content == NULL)
		new_content = ft_strdup(char_str);
	else
	{
		old_content = tok->content;
		new_content = ft_strjoin(old_content, char_str);
		free(old_content);
	}
	if (!new_content)
		return (-1);
	tok->content = new_content;
	return (EXIT_SUCCESS);
}

int	append_str_to_content(t_token *tok, char *str)
{
	char	*new_content;
	char	*old_content;

	if (tok->content == NULL)
		new_content = ft_strdup(str);
	else
	{
		old_content = tok->content;
		new_content = ft_strjoin(old_content, str);
		free(old_content);
	}
	if (!new_content)
		return (-1);
	tok->content = new_content;
	return (EXIT_SUCCESS);
}

int	collect_word_content(char *line, int *i_ptr, t_token *tok)
{
	int		i;
	char	c;

	i = *i_ptr;
	while (line[i])
	{
		c = line[i];
		if (should_break_word(c, tok->quote))
			break ;
		if (is_quote(c))
		{
			if (handle_quote_char(tok, c))
			{
				i++;
				continue ;
			}
		}
		if (append_char_to_content(tok, c) < 0)
			return (-1);
		i++;
	}
	if (tok->quote != QUOTE_NORMAL)
		return (-1);
	if (tok->content == NULL)
		tok->content = ft_strdup("");
	return (*i_ptr = i, EXIT_SUCCESS);
}
