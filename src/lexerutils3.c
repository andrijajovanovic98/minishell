/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:35:44 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/12 10:48:15 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	identify_general_token(t_var *var, char **start, char **end)
{
	int	type;

	if (!**start)
		return (END);
	if (identify_nonexistent_var(var, start, end))
		return (NO_VAR);
	type = CMD;
	while (**end && !ft_strchr("< >|\t", **end))
	{
		if (**end == '\'' && identify_single_quotes(end, end))
			type = INTERPRET;
		else if (**end == '\"' && identify_double_quotes(end, end))
			type = INTERPRET;
		else if (**end == '$')
			type = INTERPRET;
		(*end)++;
	}
	return (type);
}

int	identify_single_quotes(char **start, char **end)
{
	char	*tmp;

	tmp = *end;
	if (**start == '\'')
	{
		*end = *start;
		(*end)++;
		while (**end)
		{
			if (**end == '\'')
				return (true);
			(*end)++;
		}
	}
	*end = tmp;
	return (false);
}

int	identify_double_quotes(char **start, char **end)
{
	char	*tmp;

	tmp = *end;
	if (**start == '\"')
	{
		*end = *start;
		(*end)++;
		while (**end)
		{
			if (**end == '\"')
				return (true);
			(*end)++;
		}
	}
	*end = tmp;
	return (false);
}

int	identify_token_type(t_var *var, char **start, char **end)
{
	int	type;

	type = identify_pipe(start, end);
	if (type != 0)
		return (type);
	type = identify_input_redirection(start, end);
	if (type != 0)
		return (type);
	type = identify_output_redirection(start, end);
	if (type != 0)
		return (type);
	return (identify_general_token(var, start, end));
}
