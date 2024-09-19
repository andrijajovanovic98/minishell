/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:35:45 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 17:58:57 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_tmp_file(t_node *node)
{
	int		i;
	int		len;
	char	*file;

	node->content[FILENAME] = malloc(BUFFER_SIZE * sizeof (char));
	if (!node->content[FILENAME])
		return (-1);
	file = node->content[FILENAME];
	ft_strlcpy(file, TMP_PATH, BUFFER_SIZE);
	i = ft_strlen(file);
	len = i + 10;
	while (i < len)
	{
		file[i] = ft_rand_alnum((size_t)node, i);
		i++;
	}
	file[i] = 0;
	return (open(file, O_CREAT | O_WRONLY, 0644));
}

char	*expand_heredoc_line(t_var *var, char *line)
{
	size_t	len;
	char	*str;

	if (!line)
		return (NULL);
	if (heredoc_line_possible_var(var, line))
		heredoc_expand_line_len(var, line);
	else
		return (line);
	len = ft_strlen(line);
	str = ft_calloc(var->len + 1, sizeof (char));
	if (!str)
		return (perror("heredoc"), free(line), NULL);
	while (*line)
	{
		if (possible_var(var, *line, *(line + 1)))
			cat_env_var(var, str, &line, line);
		else
			cat_char_to_str(str, *line, var->len + 1);
		line++;
	}
	return (free(line - len), str);
}

bool	write_heredoc_line(t_var *var, int fd, char *line, int expand)
{
	ssize_t	len;

	if (expand)
		line = expand_heredoc_line(var, line);
	if (!line)
		return (false);
	len = write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (len != -1);
}

void	write_doc(t_var *var, char *limiter, int fd, int expand)
{
	extern sig_atomic_t	g_signal;
	char				*line;

	sigint_handler_interactive_mode(var);
	if (TESTER)
		line = trim_nl_free(get_next_line(STDIN_FILENO));
	else
		line = readline(heredoc_prompt(var, limiter));
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) \
	&& !g_signal)
	{
		if (!write_heredoc_line(var, fd, line, expand))
			return (perror("heredoc"), \
			free_heredoc_prompt(var), status(var, 1));
		if (TESTER)
			line = trim_nl_free(get_next_line(STDIN_FILENO));
		else
			line = readline(var->prompt);
	}
	sigint_handler_non_interactive_mode(var);
	free_heredoc_prompt(var);
	if (!line)
		heredoc_warning(g_signal, limiter);
	free(line);
}

int	write_here_docs(t_var *var)
{
	t_node	*node;
	int		fd;

	node = get_next_node(var->list, HEREDOC, END);
	while (node && !var->status)
	{
		fd = create_tmp_file(node);
		if (fd == -1)
			return (perror("heredoc"), status_1(var), false);
		write_doc(var, node->content[2], fd, !(node->type & NO_EXPAND));
		close(fd);
		check_received_signal(var);
		if (var->status)
			return (false);
		node = get_next_node(node->next, HEREDOC, END);
	}
	return (true);
}
