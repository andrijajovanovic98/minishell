/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:46:46 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/21 11:02:02 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char(char c, int *len)
{
	int	written_chars;

	written_chars = write(1, &c, 1);
	if (written_chars == -1)
		*len = -1;
	else
		*len += 1;
}

void	print_string(char *str, int *len)
{
	int	written_chars;

	written_chars = 0;
	if (!str)
		print_string("(null)", len);
	else
		written_chars = write(1, str, ft_strlen(str));
	if (written_chars == -1)
		*len = -1;
	else
		*len += written_chars;
}

void	print_decimal(long long n, int *len)
{
	char	*str;

	str = ft_itoa(n);
	print_string(str, len);
	free(str);
}

void	print_pointer(void *ptr, int *len)
{
	unsigned long long	p;

	p = (unsigned long long)ptr;
	if (p == 0)
		print_string("(nil)", len);
	else
	{
		print_string("0x", len);
		if (*len != -1)
			print_hex(p, 'x', len);
	}
}

void	print_hex(unsigned long long n, char x, int *len)
{
	unsigned long long	mask;
	char				radix[17];
	char				hex_number[17];
	int					i;

	if (n == 0)
	{
		print_char('0', len);
		return ;
	}
	mask = 0xF;
	if (x == 'x')
		ft_strlcpy(radix, "0123456789abcdef", 17);
	else
		ft_strlcpy(radix, "0123456789ABCDEF", 17);
	i = -1;
	while (++i < 16)
		hex_number[i] = radix[n >> (4 * (15 - i)) & mask];
	hex_number[i] = 0;
	i = 0;
	while (hex_number[i] == '0')
		i++;
	print_string(&hex_number[i], len);
}
