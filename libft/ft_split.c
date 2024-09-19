/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:34:03 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/05 19:02:33 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	delimiter_len(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s == c && *s)
	{
		s++;
		n++;
	}
	return (n);
}

static int	word_len(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s != c && *s)
	{
		s++;
		n++;
	}
	return (n);
}

int	count_words(char const *s, char c)
{
	int		n;

	n = 0;
	while (s && *s)
	{
		s += delimiter_len(s, c);
		if (*s)
			n++;
		s += word_len(s, c);
	}
	return (n);
}

static int	allocate_words(char const *s, char c, char **ret)
{
	size_t	len;
	int		i;

	i = 0;
	s += delimiter_len(s, c);
	while (*s)
	{
		len = word_len(s, c);
		ret[i] = malloc((len + 1) * sizeof (char));
		if (!ret[i])
			return (free_string_array(ret), 0);
		ft_strlcpy(ret[i], s, len + 1);
		s += len;
		s += delimiter_len(s, c);
		i++;
	}
	ret[i] = (char *)0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = (char **)malloc((count_words(s, c) + 1) * sizeof (char *));
	if (!ret)
		return (NULL);
	if (!allocate_words(s, c, ret))
		return (NULL);
	return (ret);
}
/* 
int main(int argc, char** argv)
{
	char **array2;
	int	i;

	array2 = ft_split("split  ||this|for|me|||||!|", '|');
	if (!array2)
		return (1);
	i = 0;
	while (array2[i] != NULL)
	{
        ft_printf("%s\n", array2[i]);
		free(array2[i]);
		i++;
	}
	free(array2[i]);
	free(array2);
    return 0;
}
*/