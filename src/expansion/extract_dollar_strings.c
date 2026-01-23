/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_dollar_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:56:44 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/21 12:53:40 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_dollar_strings(char **dollar_split, char *str)
{
	int	i;
	int	len;
	int	start;
	int	j;

	i = 0;
	len = 0;
	start = 0;
	j = 0;
	if (str[0] == '$')
	{
		len = find_char(&str[1], '$');
		if (len == -1)
			len = ft_strlen(&str[1]);
		dollar_split[j++] = ft_substr(str, 1, len);
		start = len;
	}
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\0')
				dollar_split[j++] = ft_strdup("$");
			else
			{
				len = find_char(&str[i], '$');
				if (len == -1)
					len = ft_strlen(&str[i]);
				dollar_split[j++] = ft_substr(str, start, len);
			}
			start = i + 1;
		}
		if (dollar_split[j - 1] == NULL)
			return (NULL);
		i++;
	}
	return (dollar_split);
}
