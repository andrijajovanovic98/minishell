/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:35:25 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/08 16:51:09 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_whitespace(char **input)
{
	while (ft_iswhitespace(**input))
		(*input)++;
}

void	ft_strncpy(char	*dest, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, s, n);
	return (dest);
}

void	add_token_to_list(t_var *var, t_token *new_token)
{
	if (!var->tokens && !var->last_token)
	{
		var->tokens = new_token;
		var->tokens->left = NULL;
		var->last_token = new_token;
	}
	else
	{
		new_token->left = var->last_token;
		var->last_token->right = new_token;
		var->last_token = new_token;
	}
}
