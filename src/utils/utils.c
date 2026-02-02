/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:34:17 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/02 14:34:19 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*increment_shlvl(char *str)
{
	char	*level;
	char	*shlvl;
	int		num;

	shlvl = NULL;
	level = ft_extract_digits(str);
	if (!level)
		return (NULL);
	num = ft_atoi(level);
	free(level);
	level = ft_itoa(num + 1);
	if (!level)
		return (NULL);
	shlvl = ft_strjoin("SHLVL=", level);
	if (!shlvl)
		return (free(level), NULL);
	free(level);
	if (VERBOSE)
		printf("SHLVL\n\n%s\n", shlvl);
	return (shlvl);
}

static int	ft_check_set(char const *set, char const c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_count_digits(char const *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_extract_digits(char const *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;
	char	*digits;

	if (!str)
		return (NULL);
	digits = "0123456789";
	len = ft_count_digits(str);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_set(digits, str[i]))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
