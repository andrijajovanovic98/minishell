/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:50:58 by szilas            #+#    #+#             */
/*   Updated: 2024/07/15 10:55:37 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tripl_ptrs(char ***ptrs, int len)
{
	if (!ptrs)
		return ;
	if (*ptrs)
	{
		while (len--)
			free_string_array(ptrs[len]);
	}
	free(ptrs);
}

char	***argv_splitter(int argc, char const *argv[])
{
	int		i;
	char	***argv_split;

	i = 0;
	argv_split = malloc(argc * sizeof (char **));
	while (argv_split && i < argc)
	{
		argv_split[i] = ft_split(argv[i], ' ');
		if (!argv_split[i])
			return (free_tripl_ptrs(argv_split, i), NULL);
		i++;
	}
	return (argv_split);
}
