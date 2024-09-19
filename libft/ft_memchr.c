/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:46:29 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:53:37 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (s && i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)(unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
/*

#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch;
    int n;

    (void)argc;
    printf("char to find in argv[1]: ");
    scanf("%c", &ch);
    printf("how many bytes to search: ");
    scanf("%d", &n);
    printf("   memchr |%c| is |%s|\n", ch, (char*)memchr(argv[1], ch, n));
    printf("ft_memchr |%c| is |%s|\n", ch, (char*)ft_memchr(argv[1], ch, n));
    return 0;
}
*/
