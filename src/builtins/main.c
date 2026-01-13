/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:19:57 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/11 15:07:03 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>




size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}
char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	if (src == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*




void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *) s;
	while (i < n)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *) s);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			total;

	if (size == 0 || nmemb == 0)
		return (malloc(0));

	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	return (ft_bzero(p, total));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	sub = NULL;
	i = 0;
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_calloc(1, sizeof(char)));
	if (len > str_len - start)
		len = str_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


int	find_equal(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '=')
			return i;
		i++;
	}
	return -1;
}

char	*get_key(char *str)
{
	int equal = find_equal(str);
	if (equal == -1)
		return (str);
	return (ft_substr(str, 0, equal));
} */


int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) ptr1;
	s2 = (unsigned char *) ptr2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < num)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	main(void)
{
	char *str = ft_strdup("PATH");
	char *str2 = ft_strdup("PATH=");

	int diff;
	diff = 0;
	if(ft_memcmp(str2, str, ft_strlen(str) + 1) == 61)
		diff = 61;

	printf("NUMM = %i\n", diff);

	return (0);
}
