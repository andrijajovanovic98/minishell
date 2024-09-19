/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:32:29 by bszilas           #+#    #+#             */
/*   Updated: 2024/04/02 16:42:58 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int c1 = '\0';
	int c2 = 128;
	int c3 = 0;
	int c4 = -1;
	int c5 = 127;

    printf("isascii('\\0'): %d\n", isascii(c1));
    printf("isascii(128): %d\n", isascii(c2));
    printf("isascii(0): %d\n", isascii(c3));
    printf("isascii(-1): %d\n", isascii(c4));
    printf("isascii(127): %d\n", isascii(c5));

	printf("ft_isascii('\\0'): %d\n", ft_isascii(c1));
    printf("ft_isascii(128): %d\n", ft_isascii(c2));
    printf("ft_isascii(0): %d\n", ft_isascii(c3));
    printf("ft_isascii(-1): %d\n", ft_isascii(c4));
    printf("ft_isascii(127): %d\n", ft_isascii(c5));
}
*/