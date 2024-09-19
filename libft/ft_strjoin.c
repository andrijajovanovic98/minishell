/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:26:46 by marvin            #+#    #+#             */
/*   Updated: 2024/08/16 20:39:23 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	ssize_t	i;

	if (!s2)
		return (free((char *)s1), NULL);
	if (!s1)
		return (ft_strdup(s2));
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = 0;
	return (free((char *)s1), ret);
}

char	*ft_strjoin_nofree(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != 0)
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i] != 0)
		ret[j++] = s2[i++];
	ret[j] = 0;
	return (ret);
}
/*
int main(int argc, char const *argv[])
{
	char *s1 = "my favorite animal is";
	char *s2 = " ";
	char *s3 = "the nyancat";
	char *tmp = ft_strjoin(s1, s2);
	char *res = ft_strjoin(tmp, s3);
	printf("%s\n", res);
	free(res);
	free(tmp);
	return 0;
}
*/