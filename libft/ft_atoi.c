/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:48:22 by bszilas           #+#    #+#             */
/*   Updated: 2024/06/13 14:13:39 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iswhitespace(char c)
{
	if (c == ' ' || (c <= '\r' && c >= '\t'))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long long	n;
	int			sign;

	if (!nptr)
		return (0);
	n = 0;
	sign = 1;
	while (iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + (*nptr++ - '0');
	return (n * sign);
}

long	ft_atol(const char *nptr)
{
	long long	n;
	int			sign;

	if (!nptr)
		return (0);
	n = 0;
	sign = 1;
	while (iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + (*nptr++ - '0');
	return (n * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("\007 8\n");
	printf("\010 9");
	char *string = "";
	printf("atoi:    %d\n", atoi(string));
	printf("ft_atoi: %d\n", ft_atoi(string));
	return 0;
}
*/