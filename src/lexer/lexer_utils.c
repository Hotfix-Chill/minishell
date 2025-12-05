/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:26:29 by abita             #+#    #+#             */
/*   Updated: 2025/12/03 14:26:31 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *line, int i)
{
	while (line[i] && line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
	return (i);
}
int ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	else	
		return (0);
}