/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:16:25 by bszilas           #+#    #+#             */
/*   Updated: 2024/07/15 10:43:12 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!big || !little)
		return (NULL);
	if (*little == 0)
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big && len > 0)
	{
		if (*big == *little && little_len <= len && \
			ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
/*
int main(int argc, char const *argv[])
{
	char	s_with_null[] = "the \0 lol";
	char	big_with_null[] = "this is a big string with the \0 char";
	
	size_t len = strlen(big_with_null);
	printf("ft_strnstr: %s\n", ft_strnstr(big_with_null, s_with_null, len));

	char *s1 = "MZIRIBMZE123";
	char *s2 = "MZIRIBMZE";
	size_t max = strlen(s2);
	printf("%s\n", ft_strnstr(s1, s2, max));
	
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	printf("%s\n", ft_strnstr(haystack, needle, 0));
	return 0;
}
*/