/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:38:56 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/13 15:34:33 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*last_node(t_token *current, t_node *this)
{
	this->content = malloc(2 * sizeof (char *));
	if (!this->content)
	{
		free(this);
		return (NULL);
	}
	this->content[0] = current->str;
	this->content[1] = NULL;
	this->type = END;
	return (this);
}

t_node	*new_command_node(t_token *current, t_node *this)
{
	t_token	*tmp;
	int		arg_count;
	int		i;

	arg_count = token_arg_count(current);
	this->content = malloc((arg_count + 1) * sizeof (char *));
	if (!this->content)
	{
		free(this);
		return (NULL);
	}
	i = 0;
	tmp = current;
	this->content[i++] = tmp->str;
	while (i < arg_count)
	{
		tmp = find_next_arg_token(tmp->right);
		this->content[i++] = tmp->str;
	}
	this->content[i] = NULL;
	this->type = CMD;
	return (this);
}

t_node	*new_pipe_node(t_token *current, t_node *this)
{
	this->content = malloc(2 * sizeof (char *));
	if (!this->content)
	{
		free(this);
		return (NULL);
	}
	this->content[0] = current->str;
	this->content[1] = NULL;
	this->type = PIPE;
	return (this);
}

t_node	*new_redirect_node(t_token *current, t_node *this)
{
	int	i;

	i = 0;
	this->type = current->type;
	if (this->type & HEREDOC)
		this->content = malloc(4 * sizeof (char *));
	else
		this->content = malloc(3 * sizeof (char *));
	if (!this->content)
		return (free(this), NULL);
	this->content[i++] = current->str;
	if (this->type & HEREDOC)
		this->content[i++] = NULL;
	current = current->right;
	if (current->type != CMD)
	{
		unexpected_token(current->str);
		return (free(this->content), free(this), NULL);
	}
	this->content[i++] = current->str;
	this->content[i] = NULL;
	return (this);
}

t_node	*new_list_node(t_token *current)
{
	t_node	*new;

	new = malloc(sizeof (t_node));
	if (!new)
		return (NULL);
	if (current->type == END)
		return (last_node(current, new));
	if (current->type == CMD)
		return (new_command_node(current, new));
	if (current->type == PIPE)
		return (new_pipe_node(current, new));
	else
		return (new_redirect_node(current, new));
}
