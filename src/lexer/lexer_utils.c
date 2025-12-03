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

int	skip_whitespaces(char *line, int i)
{
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || 
			line[i] == '\r' || line[i] == '\v' || line[i] == 'f')
			i++;
		else
			break ;
	}
	return (i); // return the index of the first non whitespace character
}
