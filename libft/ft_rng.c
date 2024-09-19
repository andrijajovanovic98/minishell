/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rng.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:27:36 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/01 15:40:01 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rng(size_t seed, int nth)
{
	int	i;
	int	n;

	n = seed % INT_MAX;
	i = 0;
	while (i++ < nth)
		n = (n * (INT_MAX - 18) + 3) % INT_MAX;
	return (n);
}

char	ft_rand_alnum(size_t seed, int nth)
{
	char	c;

	c = (char)ft_rng(seed, nth);
	while (!ft_isalnum(c))
		c += 42;
	return (c);
}
/* 
int main(int argc, char const *argv[])
{
	for (size_t i = 0; i < 50; i++)
		ft_printf("%d\n", (ft_rng((size_t)argv, i)));
	for (size_t i = 0; i < 50; i++)
		ft_printf("%c\n", (ft_rand_alnum((size_t)argv, i)));
	return 0;
}
 */