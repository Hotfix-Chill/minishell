/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:00:02 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/02 05:46:25 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	long long	num;
	int			minus;
	bool		minus_flag;

	num = 0;
	minus = 1;
	ft_skip_whitespaces(&str);
	minus_flag = ft_skip_signs(&str);
	if (minus_flag)
		minus = -1;
	ft_skip_zeros(&str);
	while (*str >= 48 && *str <= 57)
	{
		num = num * 10;
		num = num + *str - '0';
		str++;
	}
	return (minus * num);
}
