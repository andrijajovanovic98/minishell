/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:35:08 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/12 12:34:13 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_token(t_token *new, char *str, int type)
{
	new->type = type;
	new->str = str;
	new->right = NULL;
}

t_token	*create_token(int type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (free(str), NULL);
	init_token(token, str, type);
	return (token);
}

char	*tokenize_str(t_var *var, char *start, char *end, int *type)
{
	char	*str;

	str = NULL;
	var->len = end - start;
	if (!(*type & (INTERPRET | NO_VAR)))
		str = ft_strndup(start, var->len);
	else
	{
		var->len = interpreted_str_len(var, start, end);
		str = cat_intrd_str(var, start, end);
		if (ambiguous_redirect(var, *type, str))
		{
			free(str);
			str = ft_strndup(start, end - start);
			*type = CMD;
		}
		else if (*type & INTERPRET)
			*type = CMD;
	}
	return (str);
}

int	add_token(t_var *var, char **start)
{
	t_token	*new_token;
	char	*end;
	int		type;
	char	*str;

	end = *start;
	type = identify_token_type(var, start, &end);
	str = tokenize_str(var, *start, end, &type);
	if (!str)
		return (false);
	*start = end;
	if (ft_strchr(str, TO_SPLIT))
		return (handle_compound_tokens(var, str));
	new_token = create_token(type, str);
	if (!new_token)
		return (false);
	add_token_to_list(var, new_token);
	return (true);
}

t_token	*tokenize(t_var *var)
{
	char	*start;

	start = var->line;
	var->last_token = NULL;
	while (*start)
	{
		skip_whitespace(&start);
		if (!*start)
			break ;
		if (!add_token(var, &start))
			return (free_tokens(var), NULL);
	}
	if (!add_token(var, &start))
		return (free_tokens(var), NULL);
	return (var->tokens);
}
