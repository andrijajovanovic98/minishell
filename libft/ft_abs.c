/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:04:23 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/26 13:27:55 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	int	mask;

	mask = n >> ((sizeof (int) * BYTE) - 1);
	return ((n + mask) ^ mask);
}
/* 
#include <stdio.h>

int main()
{
	int n = -1;
	int n2 = INT_MIN + 1;
	int n3 = 0;
	int n4 = 1;
	printf("%d\n%d\n%d\n%d\n", ft_abs(n), ft_abs(n2), ft_abs(n3), ft_abs(n4));
	return 0;
}
 */