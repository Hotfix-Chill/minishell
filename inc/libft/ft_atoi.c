/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:36:15 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/03 23:11:29 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		minus;
	bool	minus_flag;
	size_t	num;

	minus = 1;
	num = 0;
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
// #include <stdio.h>
// int	main(void)
// {
// 	char	*c =  ft_strdup("-2147483648");
// 	int		num;

// 	num = ft_atoi(c);
// 	printf("Nummer: %d\n", num);

// 	num = atoi("-2147483648");
// 	printf("Nummer: %d\n", num);
// }
