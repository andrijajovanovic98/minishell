/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:56:58 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 13:48:45 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
		return (0);
	return (1);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	for (int i = -1; i < 530; i++)
	{
		if (isalpha(i) != ft_isalpha(i))
		{
			printf("error at%d\n", i);
		}
	}
	printf("no error at all");
}
*/