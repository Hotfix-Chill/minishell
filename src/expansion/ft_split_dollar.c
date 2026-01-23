/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:56:44 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/23 12:26:59 by pjelinek         ###   ########.fr       */
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
		return (NULL);
	words = wordcount(s, c);
	if (words == -1)
		return (NULL);
	split = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_loop(split, s, c));
}
