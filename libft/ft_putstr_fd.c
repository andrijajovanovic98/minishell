/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:00:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 23:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
/*
int main(int argc, char const *argv[])
{
	char	*str = "print\n\0 dont print";
	char *s1 = "\x12\xff\x65\x12\xbd\xde\xad\n";
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(s1, 1);
	return 0;
}
*/