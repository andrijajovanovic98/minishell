/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:34 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 14:04:20 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	char			*ret;
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == ch)
		{
			ret = (char *)&s[len];
			return (ret);
		}
		len--;
	}
	return (NULL);
}
