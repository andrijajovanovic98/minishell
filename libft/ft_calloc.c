/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:27:47 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:38:10 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*buf;

	if (nitems * (double)size > (double)LONG_MAX)
		return (NULL);
	buf = malloc(nitems * size);
	if (!buf)
		return (NULL);
	ft_bzero(buf, nitems * size);
	return (buf);
}
/*
#include <stdio.h>

int main(int argc, char const *argv[])
{
	return 0;
}
*/