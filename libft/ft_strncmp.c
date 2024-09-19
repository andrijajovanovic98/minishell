/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:51:01 by bszilas           #+#    #+#             */
/*   Updated: 2024/07/15 08:50:13 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (- (unsigned char)s2[0]);
	if (!s2)
		return ((unsigned char)s1[0]);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == 0)
			return (0);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(int argc, char const *argv[])
{
	size_t	n;

//	printf("How many chars to compare:");
//	scanf("%zu", &n);
//	printf("   strncmp: %d\n", strncmp(argv[1], argv[2], n));
//	printf("ft_strncmp: %d\n", strncmp(argv[1], argv[2], n));
	
	char *s1 = "\x12\xff\x65\x12\xbd\xde\xad";
	char *s2 = "\x12\x02";
	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("   strncmp: %d\n", strncmp(s1, s2, n));
	printf("ft_strncmp: %d\n", ft_strncmp(s1, s2, n));	
	return 0;
}
*/