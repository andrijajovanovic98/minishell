/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:39:22 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 16:16:03 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirect_infile(t_var *var, char *file)
{
	var->in_fd = open(file, O_RDONLY);
	if (var->in_fd == -1)
	{
		perror(file);
		free_all(var);
		exit(EXIT_FAILURE);
	}
	if (dup2(var->in_fd, STDIN_FILENO) == -1)
	{
		perror("infile: dup2");
		free_all(var);
		exit(EXIT_FAILURE);
	}
	close(var->in_fd);
}

void	redirect_outfile(t_var *var, char *file, int type)
{
	var->out_fd = open(file, O_WRONLY | O_CREAT | type, 0644);
	if (var->out_fd == -1)
	{
		perror(file);
		free_all(var);
		exit(EXIT_FAILURE);
	}
	if (dup2(var->out_fd, STDOUT_FILENO) == -1)
	{
		perror("outfile: dup2");
		free_all(var);
		exit(EXIT_FAILURE);
	}
	close(var->out_fd);
}

void	redirect_or_exit(t_var *var)
{
	t_node	*node;

	node = get_next_node(var->current, REDIRECTION, PIPE | END);
	while (node)
	{
		if (node->type & AMBI_R)
		{
			ambiguous_redirect_error(var, node->content[FILENAME]);
			free_all(var);
			exit(var->status);
		}
		if (node->type & (HEREDOC | IN_R))
			redirect_infile(var, node->content[FILENAME]);
		else if (node->type & (O_TRUNC | O_APPEND))
			redirect_outfile(var, node->content[FILENAME], node->type);
		node = get_next_node(node->next, REDIRECTION, PIPE | END);
	}
}

int	open_files_in_parent(t_var *var)
{
	t_node	*node;
	int		fd;

	node = get_next_node(var->list, IN_R | O_TRUNC | O_APPEND, END);
	if (!node)
		return (true);
	fd = INT_MAX;
	while (node)
	{
		if (node->type & AMBI_R)
		{
			ambiguous_redirect_error(var, node->content[FILENAME]);
			return (false);
		}
		if (node->type == IN_R)
			fd = open(node->content[FILENAME], O_RDONLY);
		else if (node->type & (O_TRUNC | O_APPEND))
			fd = open(node->content[1], O_WRONLY | O_CREAT | node->type, 0644);
		if (fd == -1)
			return (perror(node->content[FILENAME]), false);
		close(fd);
		node = get_next_node(node->next, IN_R | O_TRUNC | O_APPEND, END);
	}
	return (true);
}
