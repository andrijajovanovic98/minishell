/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:55:04 by bszilas           #+#    #+#             */
/*   Updated: 2024/07/15 10:42:16 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (NULL);
	while (n--)
		*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	return (dest);
}
/*
#include <stdio.h>

int main(int argc, char *argv[])
{
   char dest[50] = "42Vienna";
   char ft_dest[50] = "42Vienna";

   memcpy(dest, argv[argc - 1], (strlen(argv[1])));
   printf("After    memcpy    dest = %s\n", dest);
   ft_memcpy(ft_dest, argv[argc - 1], (strlen(argv[1])));
   printf("After ft_memcpy ft_dest = %s\n", ft_dest);
	printf("ft_memcpy dest: %p\n", ft_memcpy(((void*)0), ((void*)0), 3));
	printf("memcpy dest:    %p\n", memcpy(((void*)0), ((void*)0), 3));

    return 0;
}
*/