/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szilas <szilas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:34 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/29 22:12:13 by szilas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (!size)
		return (ft_strlen(src));
	while ((size - i - 1) > 0 && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	while (src[i] != 0)
		i++;
	return (i);
}
/*
#include <stdio.h>

int main(int argc, char const *argv[])
{
    (void)argc;

	char str[] = "BBBB";
	char buf[] = "AAAAAAAA";
	printf("String: %s\n", buf);
    printf("ft_strlcpy return: %zu\nString: %s\n",\
	ft_strlcpy(buf, str, (ft_strlen(str) + 1)), buf);
    return 0;
	
}
*/