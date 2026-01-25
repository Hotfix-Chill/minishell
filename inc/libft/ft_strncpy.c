/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:47:39 by pjelinek          #+#    #+#             */
/*   Updated: 2026/01/20 19:54:33 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst || !src || len <= 0)
		return (NULL);
	while (i + 1 < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
int main()
{
    char quelle[] = "abc123456";
    char ziel[15];

    size_t result = ft_strlcpy(ziel, quelle, 5);

    printf("Ziel: %s\n", ziel);
    printf("Länge von Quelle: %zu\n", result);

    return 0;
} */
