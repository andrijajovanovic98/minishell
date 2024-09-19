/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_compound_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:14:38 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/08 14:03:37 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ambiguous_redirect(t_var *var, int type, char *str)
{
	t_token	*last;

	last = var->last_token;
	if (last && last->type & (REDIRECTION))
	{
		if ((str && count_words(str, TO_SPLIT) > 1) || type == NO_VAR)
		{
			last->type = last->type | AMBI_R;
			return (true);
		}
	}
	return (false);
}

void	free_bare_tokens(t_token *last)
{
	t_token	*ptr;
	t_token	*current;

	ptr = last->right;
	while (ptr)
	{
		current = ptr;
		ptr = ptr->right;
		free(current);
	}
	last->right = NULL;
}

int	split_compound_tokens(t_var *var, char *str)
{
	char	**split;
	size_t	token_count;
	size_t	i;
	t_token	*new;
	t_token	*last;

	split = ft_split(str, TO_SPLIT);
	if (!split)
		return (false);
	last = var->last_token;
	token_count = 0;
	while (split[token_count])
		token_count++;
	i = 0;
	while (i < token_count)
	{
		new = malloc(sizeof (t_token));
		if (!new)
			return (free_string_array(split), free_bare_tokens(last), false);
		init_token(new, split[i], CMD);
		add_token_to_list(var, new);
		i++;
	}
	return (free(split), true);
}

bool	handle_compound_tokens(t_var *var, char *str)
{
	bool	ok;

	ok = split_compound_tokens(var, str);
	free(str);
	return (ok);
}
