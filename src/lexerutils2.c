/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:35:44 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/09 10:12:16 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	identify_input_redirection(char **start, char **end)
{
	if (**start == '<')
	{
		if (*(*start + 1) == '<')
		{
			*end += 2;
			return (HEREDOC);
		}
		*end += 1;
		return (IN_R);
	}
	return (0);
}

int	identify_output_redirection(char **start, char **end)
{
	if (**start == '>')
	{
		if (*(*start + 1) == '>')
		{
			*end += 2;
			return (O_APPEND);
		}
		*end += 1;
		return (O_TRUNC);
	}
	return (0);
}

int	identify_pipe(char **start, char **end)
{
	if (**start == '|')
	{
		*end += 1;
		return (PIPE);
	}
	return (0);
}

char	*token_end(char *start)
{
	while (*start && !ft_strchr("< >|\t", *start))
		start++;
	return (start);
}

void	reset_end(char *start, char **end, char *ptr, char *tkn_end)
{
	if (ptr != tkn_end)
		*end = start;
	else
		*end = tkn_end;
}
