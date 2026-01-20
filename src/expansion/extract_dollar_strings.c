/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_dollar_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:56:44 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/20 18:59:52 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**extract_dollar_strings(char **dollar_split, char *str)
{
	int	i;
	int	len = 0;
	int	start = 0;
	int	j = 0;

	i = 0;

	if (str[0] == '$')
	{
		int len = find_char(&str[1], '$');
		if (len == -1)
			len = ft_strlen(&str[1]);
		dollar_split[j++] = ft_substr(str, 1, len);
		start = len;
		printf("AT START LEN:%i\n", len);
		printf("dollar split[%i]: %s\n", j - 1, dollar_split[j - 1]);
	}
	while (str[i])
	{

		if (str[i] == '$')
		{

			if (str[i + 1] == '\0')
				dollar_split[j++] = ft_strdup("$");
			else
			{
				printf("BEFORE LEN:%i\n", len);

				len = find_char(&str[i], '$');
				printf("AFTER FIND DOLLAR LEN:%i\n", len);

				if (len == -1)
					len = ft_strlen(&str[i]);
				printf("AFTER FIND NULLTERMINATOR  LEN:%i\n", len);

				dollar_split[j++] = ft_substr(str, start, len);
			}
			printf("LEN; %i, START: %i\n", len, start);
			start = i + 1;
		//	printf("dollar split[%i]: %s\n", j - 1, dollar_split[j - 1]);

		}
		if (dollar_split[j - 1] == NULL)
			return (NULL);
		i++;
	}
	return (dollar_split);
}
