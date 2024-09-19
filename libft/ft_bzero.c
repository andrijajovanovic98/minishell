/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:45:12 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:56:05 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (s && n--)
		*((unsigned char *)s + n) = 0;
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	(void)argc;
	size_t n = 0;

	printf("how many bytes to set to zero: ");
	scanf("%lu", &n);

    printf("before: [0] = %c\n", argv[1][0]);
    printf("    [n - 1] = %c\n", argv[1][n - 1]);
    printf("        [n] = %c\n", argv[1][n]);
    ft_bzero(argv[1], n);
    printf("after:  [0] = %c\n", argv[1][0]);
    printf("    [n - 1] = %c\n", argv[1][n - 1]);
    printf("        [n] = %c\n", argv[1][n]);
    return 0;
}
*/
