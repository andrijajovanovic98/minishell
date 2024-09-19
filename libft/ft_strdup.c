/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:58:42 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 14:00:36 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	void	*buf;
	size_t	siz;

	if (!s)
		return (NULL);
	siz = (ft_strlen(s) + 1);
	buf = malloc(siz * sizeof (char));
	if (!buf)
		return (NULL);
	return ((char *)ft_memcpy(buf, (void *)s, siz));
}
