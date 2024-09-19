/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:05:03 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/17 11:47:42 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lists_and_path(t_var *var)
{
	free_linked_lists(var);
	free_string_array(var->splitted_path);
	var->splitted_path = NULL;
}

void	free_all(t_var *var)
{
	free_lists_and_path(var);
	free_string_array(var->env);
	var->env = NULL;
	free(var->cwd);
	var->cwd = NULL;
	free(var->line);
	var->line = NULL;
}

void	free_linked_lists(t_var *var)
{
	t_node	*node;

	free_tokens(var);
	var->tokens = NULL;
	while (var->list)
	{
		node = var->list;
		var->list = node->next;
		if (node->type & HEREDOC)
			free(node->content[FILENAME]);
		free(node->content);
		free(node);
	}
	var->list = NULL;
}

void	free_tokens(t_var *var)
{
	t_token	*temp;

	temp = var->tokens;
	while (temp)
	{
		var->tokens = temp->right;
		free(temp->str);
		free(temp);
		temp = var->tokens;
	}
}
