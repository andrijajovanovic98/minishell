/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:00:19 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/06 16:21:58 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	dst_len;
	size_t	src_len;

	if (!dst)
		return (0);
	if (!src)
		return (ft_strlen((const char *)dst));
	dst_len = ft_strlen((const char *)dst);
	src_len = ft_strlen((const char *)src);
	if (size < dst_len + 1)
		return (src_len + size);
	i = 0;
	while (size - dst_len - i - 1 > 0 && src[i] != 0)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}
/*
#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
	char buff2[0xF00] = "there is no stars in the sky";
	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;
	printf("size: %zu\n", max);
	printf("dst_len: %zu\n", strlen(buff2));
	printf("src_len: %zu\n", strlen(str));
	printf("return: %zu\n", ft_strlcat(buff2, str, max));
	printf("buf = %s\n", buff2);
}
*/