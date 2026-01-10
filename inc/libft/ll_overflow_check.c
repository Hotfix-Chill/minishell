/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_overflow_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 05:29:52 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/02 06:03:11 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ll_overflow_check(const char *str)
{
	const char *p;
	int	len;
	bool negativ;

	p = (char *)str;
	ft_skip_whitespaces(&p);
	negativ = ft_skip_signs(&p);
	ft_skip_zeros(&p);
	len = ft_strlen(p);
	if (len < 19)
		return (false);
	else if (len > 19)
		return (false);
	if (len == 19 && !negativ && ft_strncmp(p, "9223372036854775807", 19) <= 0)
		return (false);
	if (len == 19 && negativ && ft_strncmp(p, "9223372036854775808", 19) <= 0)
		return (false);
	return (true);
}

