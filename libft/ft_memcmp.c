/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:50:15 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:54:48 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (s1 && s2 && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(int argc, char const *argv[])
{
    (void)argc;
    int n = 0;

    printf("How many bytes to compare: ");
    scanf("%d", &n);
    printf("   memcmp argv[1] and argv[2]: %d\n", memcmp(argv[1], argv[2], n));
    printf("ft_ argv[1] and argv[2]: %d\n", ft_memcmp(argv[1], argv[2], n));
    return 0;
}
*/
