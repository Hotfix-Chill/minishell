/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_overflow_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 05:49:41 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/02 05:52:19 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool    int_overflow_check(const char *str)
{
    const char  *p;
    bool        negative;
    int         len;

    p = str;
    ft_skip_whitespaces(&p);
    negative = ft_skip_signs(&p);
    ft_skip_zeros(&p);
    len = ft_strlen(p);
	if (len < 10)
		return (false);
	if (len > 10)
		return (true);
	if (len == 10 && !negative && ft_strncmp(p, "2147483647", 10) <= 0)
		    return (false);
	if (len == 10 && negative && ft_strncmp(p, "2147483648", 10) <= 0)
		    return (false);
	return (true);
}
