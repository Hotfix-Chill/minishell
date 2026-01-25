/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_pt2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:26:04 by abita             #+#    #+#             */
/*   Updated: 2026/01/25 14:26:37 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
