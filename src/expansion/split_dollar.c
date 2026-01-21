/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:53:00 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/21 14:49:01 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static char	*ft_cpy(char const *str, char c)
{
	size_t	count;
	size_t	i;
	char	*p;

	i = 0;
	count = 0;
	while (str[count] != c && str[count] != '\0')
		count++;
	p = (char *)ft_calloc((count + 1), sizeof(char));
	if (!p)
		return (NULL);
	while (i < count && str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	ft_freeall(char **freearr, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(freearr[i]);
		i++;
	}
	free(freearr);
}

static char	**ft_split_loop(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			split[j] = ft_cpy(&s[i], c);
			if (!split[j])
				return (ft_freeall(split, j), NULL);
			j++;
			while (s[i] != c && s[i + 1] != '\0')
				i++;

		}
		i++;
	}
	if (s[i - 1] == c && s[i] == '\0')
		split[j] = ft_strdup("$");
	return (split);
}
static ssize_t	wordcount(char const *str, char c)
{
	size_t	i;
	size_t	words;
	bool	in_word;

	words = 0;
	i = 0;
	in_word = false;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (c == str[i])
			in_word = false;
		else if (!in_word)
		{
			in_word = true;
			words++;
		}
		i++;
	}
	if (str[i - 1] == '$')
		words += 1;
	return (words);
}

char	**ft_split_dollar(char const *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (printf("NULL\n"), NULL);
	words = wordcount(s, c);
	if (words == -1)
		return (NULL);

	printf("WORDCOUNT: %i\n", words);

	split = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_loop(split, s, c));
}

















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
		printf("count[%zu]: %zu\n", i - 1, count);

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

	if (VERBOSE)
		printf("INSIDE EXPAND\n");
	if (!*dollar_split)
		return (NULL);
	while (dollar_split[i])
	{
		if (dollar_split[i][0] == '$' && dollar_split[i++][1] == '\0')
			exp_word[j++] = ft_strdup("$");
		else if (dollar_split[i][0] == '?' && dollar_split[i++][1] == '\0')
			exp_word[j++] = ft_itoa(data->return_value);
		else if (first_dollar)
			exp_word[j++] = ft_strdup(dollar_split[i++]);
		else
		{
			value = extract_var(data, dollar_split[i++]);
			if (!value)
				exp_word[j++] = ft_strdup("");
			else
				exp_word[j++] = value;
		}
		first_dollar = false;
		if (exp_word[j - 1] == NULL)
			return (NULL);
	}
	printf("INDEX in EXP_WORD: %i\n", j);
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

	printf("PRINT EXPANDED STRINGS\n");
	//print_split(expanded_words);
	if (expanded_words[i + 1] == NULL)
		return (ft_strdup(expanded_words[0]));
	len = count_split_chars(expanded_words);
	printf("len: count split chars in join_expanded_strings = %zu\n", len);

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

	if (VERBOSE)
		printf("INSIDE EXPANSION - SPLIT DOLLAR\n");

	first_dollar = false;
	if (str[0] != '$')
		first_dollar = true;
	dollar_split = ft_split_dollar(str, '$');


	if (!dollar_split)
		return (printf("split cleanup\n"), NULL);

	for	(int i = 0; dollar_split[i]; i++)
		printf("dollar_split_value[%i]: %s\n", i, dollar_split[i]);


	count = count_lines(dollar_split);
	printf("ALLOCATION SIZE for exp_word: %zu\n", count + 1);

	exp_word = ft_calloc(count + 1, sizeof(char *));
	if (!exp_word)
		return (free_split(dollar_split), NULL);
	exp_word = expand(dollar_split, exp_word, data, first_dollar);
	if (!exp_word)
		return (free_split(dollar_split), free_split(exp_word), printf("22222\n"), NULL);
	final_exp_str = join_expanded_strings(exp_word);
	free_split(dollar_split);
	free_split(exp_word);
	if (!final_exp_str)
		return (NULL);
	return (final_exp_str);
}
