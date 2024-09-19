/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:47:41 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/04 14:03:07 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	digits_count(long long n, int base)
{
	size_t	len;

	len = 1;
	while (n % base != n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static int	fill_temp_arr(char *s, long long n, int max_siz)
{
	int	i;
	int	negative;

	negative = n >> ((sizeof (long long) * BYTE) - 1) & 0x1;
	if (negative)
		n *= -1;
	i = max_siz - 1;
	s[i] = 0;
	if (n == 0)
		s[--i] = '0';
	while (n > 0)
	{
		s[--i] = n % 10 + '0';
		n /= 10;
	}
	if (negative)
		s[--i] = '-';
	return (i);
}

char	*ft_itoa(long long n)
{
	char	*ret;
	int		i;
	int		max_siz;
	char	temp_arr[BUFFER_SIZE];

	max_siz = digits_count(INT_MAX, 10) + 2;
	i = fill_temp_arr(temp_arr, n, max_siz);
	ret = malloc((max_siz - i) * sizeof (char));
	if (!ret)
		return (NULL);
	ft_memcpy((void *)ret, (const void *)temp_arr + i, max_siz - i);
	return (ret);
}
/*
int main(int argc, char const *argv[])
{
	char	*n = ft_itoa(atoi(argv[1]));
	for (size_t i = 0; i <= strlen(n); i++)
		printf("[%d] = %c\n", i, n[i]);	
	free(n);
	return 0;
}
*/