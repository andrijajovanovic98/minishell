/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:07:32 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/03 14:27:00 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

/* 
int main(int argc, char const *argv[])
{
	char	***ptrs;

	ptrs = malloc(argc * sizeof (char **));
	if (!ptrs)
		return (1);
	for (int i = 0; i < argc; i++)
	{
		ptrs[i] = ft_split(argv[i], ' ');
		if (!ptrs[i])
			return (free_tripl_ptrs(ptrs, i), 0);
		for (size_t j = 0; ptrs[i][j]; j++)
			ft_printf("ptrs[%d][%d]\"%s\"\n", i, j, ptrs[i][j]);
	}
	free_tripl_ptrs(ptrs, argc);
	return 0;
}
 */