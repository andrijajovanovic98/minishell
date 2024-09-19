/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:40:36 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/07 20:43:36 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*find_next_arg_token(t_token *token)
{
	while (token && !(token->type & (PIPE | END)))
	{
		if (token->type == CMD && \
		(!token->left || !(token->left->type & REDIRECTION)))
			return (token);
		token = token->right;
	}
	return (NULL);
}

t_token	*find_token(t_token *token, int type, int before_type)
{
	while (token && !(token->type & before_type))
	{
		if (token->type & type)
			return (token);
		token = token->right;
	}
	return (NULL);
}

int	token_arg_count(t_token *current)
{
	int	count;

	count = 0;
	while (current)
	{
		count++;
		current = find_next_arg_token(current->right);
	}
	return (count);
}

void	add_to_list(t_var *var, t_node *this)
{
	t_node	*ptr;

	ptr = var->list;
	if (!ptr)
	{
		var->list = this;
		this->prev = NULL;
		this->next = NULL;
		return ;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = this;
		this->prev = ptr;
		this->next = NULL;
	}
}
