/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:43:43 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 14:38:59 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	possible_var(t_var *var, char c, char d)
{
	if (var->last_token && var->last_token->type & HEREDOC)
		return (false);
	if (!d || d == '\"')
		return (false);
	return (c == '$' && (ft_isalpha(d) || ft_strchr("_?", d)));
}

void	mark_whitespaces(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			*str = TO_SPLIT;
		str++;
	}
}

int	lone_dollar_sign(char *start, char *end)
{
	if (*start == '$')
	{
		start++;
		if (identify_double_quotes(&start, &end) \
		|| identify_single_quotes(&start, &end))
			return (true);
	}
	return (false);
}

int	identify_nonexistent_var(t_var *var, char **start, char **end)
{
	char	*tkn_end;
	char	*ptr;
	char	c;

	tkn_end = token_end(*start);
	ptr = *start;
	while (*ptr && possible_var(var, ptr[0], ptr[1]) && ptr[1] != '?')
	{
		*end = ptr + 1;
		ptr += 2;
		while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
			ptr++;
		c = *ptr;
		*ptr = 0;
		if (ft_getenv(var->env, *end))
		{
			*ptr = c;
			*end = *start;
			return (false);
		}
		*ptr = c;
	}
	reset_end(*start, end, ptr, tkn_end);
	return (ptr == tkn_end);
}
