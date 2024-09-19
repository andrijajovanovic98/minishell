/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:37:22 by bszilas           #+#    #+#             */
/*   Updated: 2024/04/08 18:22:11 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
		len = 0;
	if (len > strlen - start)
		len = strlen - start;
	sub = malloc((len + 1) * sizeof (char));
	if (!sub)
		return (NULL);
	i = 0;
	if (start < strlen)
	{
		while (s[start] != 0 && len--)
			sub[i++] = s[start++];
	}
	sub[i] = 0;
	return (sub);
}
/*
int main(int argc, char const *argv[])
{
	char * s = ft_substr("tripouille", 0, 42000);
	printf("%d\n", strcmp(s, "tripouille"));
	free(s);
	
	char *str2 = "01234";
	size_t size2 = 10;
	char *ret2 = ft_substr(str2, 10, size2);
	printf("%s\n", ret2);
	printf("%d\n", strncmp(ret2, "", 1));
	free(ret2);
	return 0;
}
*/