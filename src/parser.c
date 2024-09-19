/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:05:27 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 13:03:57 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	make_pipeline(t_var *var, t_token *start)
{
	t_token	*token;
	t_node	*new;

	token = find_token(start, REDIRECTION, PIPE | END);
	while (token)
	{
		new = new_list_node(token);
		if (!new)
			return (false);
		add_to_list(var, new);
		token = find_token(token->right, REDIRECTION, PIPE | END);
	}
	token = find_next_arg_token(start);
	if (token)
	{
		new = new_list_node(token);
		if (!new)
			return (false);
		add_to_list(var, new);
	}
	return (true);
}

t_token	*last_token(t_token *start)
{
	while (start->right)
		start = start->right;
	return (start);
}

bool	close_pipeline(t_var *var, t_token *start)
{
	t_token	*token;
	t_node	*new;

	token = find_token(start, PIPE, END);
	if (!token)
		token = last_token(start);
	new = new_list_node(token);
	if (!new)
		return (false);
	add_to_list(var, new);
	return (true);
}

bool	parse_tokens(t_var *var)
{
	t_token	*current;

	var->in_fd = STDIN_FILENO;
	var->out_fd = STDOUT_FILENO;
	var->cmds = 0;
	if (!var->tokens)
		return (status_1(var), false);
	if (!valid_syntax(var->tokens))
	{
		status(var, 2);
		return (free_tokens(var), false);
	}
	current = var->tokens;
	while (current)
	{
		if (current->type == PIPE)
			current = current->right;
		if (!make_pipeline(var, current) || !close_pipeline(var, current))
		{
			free_linked_lists(var);
			return (status_1(var), false);
		}
		current = find_token(current, PIPE, END);
	}
	return (true);
}
