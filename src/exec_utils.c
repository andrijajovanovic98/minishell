/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:13:32 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/14 15:46:42 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	txt_file(char *file)
{
	char	buf[BUFFER_SIZE];
	ssize_t	len;
	int		txt;
	int		fd;
	int		i;

	txt = true;
	ft_bzero(buf, BUFFER_SIZE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (!txt);
	len = read(fd, buf, BUFFER_SIZE);
	if (len == -1)
		txt = false;
	i = 0;
	while (i < len)
	{
		if (!ft_isprint(buf[i]) || buf[i] == '\t' || buf[i] == '\n')
			txt = false;
		i++;
	}
	close(fd);
	return (txt);
}

char	*get_cmd(t_var *var)
{
	if (!var->splitted_path || !var->splitted_path[0])
		return (check_given_file(var));
	if (!ft_strncmp("..", var->current->content[0], 3) \
	|| !ft_strncmp(".", var->current->content[0], 2))
	{
		var->status = 127;
		return (command_not_found(var), NULL);
	}
	if (search_path(var, X_OK))
	{
		if (txt_file(var->exec_cmd))
			error_exec_txt_file(var);
		return (var->exec_cmd);
	}
	if (search_path(var, F_OK))
		return (var->exec_cmd);
	command_not_found(var);
	return (NULL);
}

int	check_files(t_var *var, char *str)
{
	char	buffer[1];
	int		fd;

	if (access(str, F_OK) == -1)
	{
		error_msg(var, ": No such file or directory", 127);
		return (1);
	}
	if (access(str, X_OK) == -1)
	{
		error_msg(var, ": Permission denied", 126);
		return (1);
	}
	fd = open(str, O_RDONLY);
	if (read(fd, buffer, 1) == -1)
	{
		close(fd);
		error_msg(var, ": Is a directory", 126);
		return (1);
	}
	close(fd);
	return (0);
}

char	*check_given_file(t_var *var)
{
	char	*str;

	str = ft_strdup(var->current->content[0]);
	if (!str)
		return (status_1(var), NULL);
	if ((check_files(var, str)) == 1)
		return (free(str), NULL);
	if (access(str, X_OK) == 0)
	{
		if (txt_file(str))
			return (error_exec_txt_file(var), free(str), NULL);
		return (str);
	}
	if (access(str, F_OK) == 0)
		return (str);
	command_not_found(var);
	free(str);
	return (NULL);
}

char	**env_loop(t_var *var, char **(*f)(t_var *, char *))
{
	int	i;

	i = 1;
	if (f == &command_export && !var->current->content[i])
	{
		print_environment(var);
		if (var->out_fd != STDOUT_FILENO)
			close(var->out_fd);
	}
	while (var->current->content[i] && var->env)
		var->env = f(var, var->current->content[i++]);
	return (var->env);
}
