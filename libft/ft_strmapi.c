/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:26:33 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 10:04:49 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*ret;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc((len + 1) * sizeof (char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = f(i, (char)s[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
/*
static char my_function(unsigned int index, char c)
{
    if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
    return (c);
}

int main(int argc, char const *argv[])
{
	char *string;
	
	for (size_t i = 1; i < argc; i++)
	{
		string = ft_strmapi(argv[i], &my_function);
		ft_putendl_fd(string, 1);
		free(string);
	}
	return 0;
}
*/