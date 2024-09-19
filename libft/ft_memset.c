/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:32:24 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:57:18 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (s && n--)
		*((unsigned char *)s + n) = (unsigned char)c;
	return (s);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
		(void)argc;
		size_t n = 0;

	printf("How many bytes to set to 'A': ");
	scanf("%lu", &n);

    printf("   memset: %s\n", (char*)memset(argv[1], 'A', n));
    printf("ft_memset: %s\n", (char*)ft_memset(argv[1], 'A', n));
    return 0;
}
*/
