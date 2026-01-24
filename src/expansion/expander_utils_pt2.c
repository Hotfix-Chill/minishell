/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_pt2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:19:36 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/24 15:19:38 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
