/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:26:52 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 10:07:21 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare_chars(char s1, char const *set)
{
	while (*set)
	{
		if (*set == s1)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*end;
	int		len;

	if (!set || !s1)
		return (NULL);
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (compare_chars(*s1, set))
		s1++;
	if (*s1)
	{
		while (compare_chars(*end, set))
			end--;
	}
	len = end - (char *)s1 + 1;
	ret = malloc((len + 1) * sizeof (char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, len);
	ret[len] = 0;
	return (ret);
}
/*
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t\
	Please\n Trim me !\n   \n \n \t\t\n  ";
	char *ret = ft_strtrim(s1, " \n\t");
	printf("%s\n", ret);
	free(ret);

	char *s2 = "\t  \n\n \t\t  \n";
	char *ret2 = ft_strtrim(s2, "\n \t");

	printf("strcmp %d\n", strcmp(ret2, ""));
	printf("strcmp %d\n", ft_strncmp(ret2, "", 2));
	free(ret2);
	return 0;
}
*/