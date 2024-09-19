/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:34:07 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/28 18:43:24 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}
/*

#include <stdio.h>

int main(int argc, char const *argv[])
{
    (void)argc;
    printf("   strlen argv[1]: %zu\n", strlen(argv[1]));
    printf("ft_strlen argv[1]: %zu\n", ft_strlen(argv[1]));
    return 0;
}
*/
