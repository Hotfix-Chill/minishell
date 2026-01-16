/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:53:00 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/16 13:21:44 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		printf("%s\n",split[i]);
		i++;
	}
	printf("\n");
	return ;
}

static size_t	count_lines(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

static size_t	count_split_chars(char **split)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (split[i])
	{
		count += ft_strlen(split[i++]);
	}
	return (count);
}

static char	**expand(char **dollar_split, char **exp_word, t_data *data, bool first_dollar)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (dollar_split[i])
	{
		if (dollar_split[i][0] == '?' && dollar_split[i++][1] == '\0')
			exp_word[j++] = ft_itoa(data->return_value);
		else if (first_dollar)
			exp_word[j++] = ft_strdup(dollar_split[i++]);
		else
		{
			value = extract_var(data, dollar_split[i++]);
			if (!value)
				exp_word[j++] = ft_strdup("");
			else
				exp_word[j++] = ft_strdup(value);
		}
		first_dollar = false;
		if (exp_word[j - 1] == NULL)
			return (NULL);
	}
	return (exp_word);
}
static char	*join_expanded_strings(char **expanded_words)
{
	int		i;
	int		k;
	int		j;
	size_t	len;
	char	*full_string;

	i = 0;
	if (expanded_words[i + 1] == NULL)
		return (ft_strdup(expanded_words[0]));
	len = count_split_chars(expanded_words);
	full_string = ft_calloc(len + 1, sizeof(char));
	if (!full_string)
		return (NULL);
	k = 0;
	while (expanded_words[i])
	{
		j = 0;
		while (expanded_words[i][j])
		{
			full_string[k++] = expanded_words[i][j++];
		}
		i++;
	}
	full_string[k] = '\0';
	return (full_string);
}

char	*split_dollar(t_data *data, char *str)
{
	bool	first_dollar;
	char	**dollar_split;
	char	**exp_word;
	char	*final_exp_str;
	size_t	count;

	first_dollar = false;
	if (str[0] != '$')
		first_dollar = true;
	dollar_split = ft_split(str, '$');
	if (!dollar_split)
		return (NULL);
	count = count_lines(dollar_split);
	exp_word = ft_calloc(count + 1, sizeof(char *));
	if (!exp_word)
		return (free_split(dollar_split), NULL);
	exp_word = expand(dollar_split, exp_word, data, first_dollar);
	if (!exp_word)
		return (free_split(dollar_split), free_split(exp_word), NULL);
	final_exp_str = join_expanded_strings(exp_word);
	free_split(dollar_split);
	free_split(exp_word);
	if (!final_exp_str)
		return (NULL);
	return (final_exp_str);
}
