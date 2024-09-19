/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:38:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 09:27:05 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
static void my_function(unsigned int i, char *c) 
{
    printf("Index: %u, Character: %c\n", i, *c);
}

int main(int argc, char *argv[])
{
	for (size_t i = 1; i < argc; i++)
	{
		ft_striteri(argv[i], &my_function);
	}
	return 0;
}
*/