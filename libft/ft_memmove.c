/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szilas <szilas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:12:41 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/20 16:38:20 by szilas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*buf[1000];

	if (!dest && !src)
		return (NULL);
	while (n > 1000)
	{
		ft_memcpy(buf, src, 1000);
		ft_memcpy(dest, buf, 1000);
		n -= 1000;
		dest += 1000;
		src += 1000;
	}
	ft_memcpy(buf, src, n);
	ft_memcpy(dest, buf, n);
	return (dest);
}
/*
#include <stdio.h>

int main(int argc, char *argv[])
{
	(void)argc;
    char buf[100] = "AAAAAAAAA";
	char buf2[100] = "AAAAAAAAA";
    int n;

    printf("Number of bytes to move from argv[1] to buffer: ");
    scanf("%d", &n);
    
    printf("buffer2: %s\n", buf2);
    printf("ft_memmove: %s\n", (char*)ft_memmove(buf2, argv[1], n));
    
	printf("buffer: %s\n", buf);
    printf("   memmove: %s\n", (char*)memmove(buf, argv[1], n));

	int size = 128 * 1024 * 1024;
	char *dst = (char *)malloc(sizeof(char) * size);
	if(!dst)
		return (-1);
	char *data = (char *)malloc(sizeof(char) * size);
	if(!data)
		return (-1);
	memset(data, 'A', size);
	ft_memcpy(dst, data, size);
	printf("last char in dst: %c\n", data[size]);
	free(dst);
	free(data);

    return 0;
}
*/