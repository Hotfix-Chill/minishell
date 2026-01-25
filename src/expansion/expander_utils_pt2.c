/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_pt2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:26:04 by abita             #+#    #+#             */
/*   Updated: 2026/01/25 19:28:50 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return_value(t_data *data, char *str)
{
	char	*return_value;
	char	*sub_str;
	char	*final;

	if (str[1] == '\0')
		return (ft_itoa(data->return_value));
	else
	{
		return_value = ft_itoa(data->return_value);
		if (!return_value)
			return (NULL);
		sub_str = ft_substr(str, 1, ft_strlen(str));
		if (!sub_str)
			return (free(return_value), NULL);
		final = ft_strjoin(return_value, sub_str);
		free(return_value);
		free(sub_str);
		if (!final)
			return (NULL);
	}
	return (final);
}

void	restore_single_quote_dollar(char *str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == SQ_DOLLAR)
			str[i] = '$';
		i++;
	}
}

int	validifier_var(char *str)
{
	size_t	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '$')
			return (i);
		i++;
	}
	return (i);
}

void	help_expand_lookup(t_data *data, char *expand_str, char **final)
{
	size_t	i;

	i = 0;
	while (i < data->export_len)
	{
		if (ft_strcmp(data->export[i].key, expand_str) == 0)
		{
			*final = ft_strdup(data->export[i].value);
			return ;
		}
		i++;
	}
}

char	*partial_expansion(char *final, char *sub_str)
{
	if (!final && sub_str)
		return (sub_str);
	else if (!final && !sub_str)
		return (NULL);
	else if (final && !sub_str)
		return (final);
	return (NULL);
}
