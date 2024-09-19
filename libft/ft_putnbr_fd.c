/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:26:32 by bszilas           #+#    #+#             */
/*   Updated: 2024/04/08 11:29:19 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;

	if (n >> (sizeof (int) * 8 - 1) & 1)
	{
		write(fd, "-", 1);
		if (n == INT_MIN)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}
/*
int main(int argc, char const *argv[])
{
	ft_putnbr_fd(-2147483648, 1); write(1, "\n", 1);
	ft_putnbr_fd(2147483647, 1); write(1, "\n", 1);
	ft_putnbr_fd(-1, 1); write(1, "\n", 1);
	ft_putnbr_fd(-0, 1); write(1, "\n", 1);
	ft_putnbr_fd(1, 1); write(1, "\n", 1);
	ft_putnbr_fd(9, 1); write(1, "\n", 1);
	ft_putnbr_fd(-9, 1); write(1, "\n", 1);
	ft_putnbr_fd(-10000, 1); write(1, "\n", 1);
	ft_putnbr_fd(1000000000, 1); write(1, "\n", 1);
	return 0;
}
*/