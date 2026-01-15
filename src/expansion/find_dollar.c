/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:53:00 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/15 18:52:19 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_lines(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

char	**find_dollar(t_data *data, char *str)
{
	bool	first_dollar;
	char	**dollar_split;
	char	**exp_word;
	char	*result;
	size_t	count;

	int		i;
	int		j;

	first_dollar = false;
	if (str[0] != '$')
		first_dollar == true;
	dollar_split = ft_split(str, '$');
	if (!dollar_split)
		return (NULL);
	count = count_lines(dollar_split);
	exp_word = ft_calloc(count + 1, sizeof(char *));
	if (!exp_word)
		return (NULL);



	i = 0;
	j = 0;
	while (dollar_split[i])
	{
		if (dollar_split[i][0] == '?' && dollar_split[i][1] == '\0')
			exp_word[j++] = ft_itoa(data->return_value);
		else if (first_dollar)
		{
			exp_word[j++] = ft_strdup(dollar_split[i++]);
			first_dollar == false;
		}
		else
		{
			result = extract_env(data, dollar_split[i++]);
			if (!result)
				exp_word[j++] = ft_strdup("");
			else
				exp_word[j++] = ft_strdup(result);
		}
		if (!exp_word[j - 1])
				return (NULL);
	}
	//join them to string

	i = 0;
	while (exp_word[i])
	{
		char *tmp;

		tmp = ft_strdup(exp_word[i]);
		if (!tmp)
			return (NULL);
		if (exp_word[i + 1] != NULL)
		{
			tmp = ft_strjoin(exp_word[i], exp_word[i + 1]);
			if (!tmp)
				return (NULL);
			
		}
		i++;
	}
}
