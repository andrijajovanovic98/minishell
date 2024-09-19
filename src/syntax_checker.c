/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:49:45 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/12 14:16:48 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unexpected_token(char *str)
{
	if (!*str)
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
}

bool	double_pipe(t_token *token)
{
	return (token->type == PIPE \
	&& token->right && token->right->type & (PIPE | END));
}

bool	missing_filename(t_token *token)
{
	return (token->type & REDIRECTION
		&& token->right && token->right->type != CMD);
}

bool	pipe_in_front(t_token *token)
{
	return (token && token->type == PIPE && token->right && token->right->type);
}

bool	valid_syntax(t_token *token)
{
	if (pipe_in_front(token))
	{
		unexpected_token(token->str);
		return (false);
	}
	while (token)
	{
		if (double_pipe(token) || missing_filename(token))
		{
			unexpected_token(token->right->str);
			return (false);
		}
		token = token->right;
	}
	return (true);
}
