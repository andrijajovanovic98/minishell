/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:02:13 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 13:43:14 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_children(t_var *var)
{
	int		status;
	int		i;
	pid_t	pid;

	close_in_and_out(var);
	pid = -1;
	i = 0;
	status = 0;
	while (pid != var->pid && var->cmds)
	{
		pid = wait(&status);
		i++;
	}
	if (!var->status)
		var->status = status;
	while (i++ < var->cmds)
		wait(&status);
	get_child_exit_status(var);
}

void	get_child_exit_status(t_var *var)
{
	extern sig_atomic_t	g_signal;

	if (WIFEXITED(var->status))
		var->status = WEXITSTATUS(var->status);
	else if (WIFSIGNALED(var->status))
	{
		var->status = 128 + WTERMSIG(var->status);
		if (var->status == 128 + SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
	if (g_signal && ft_strncmp("./minishell", var->current->content[0], 12))
		write(STDOUT_FILENO, "\n", 1);
}

size_t	to_export_len(char *str)
{
	if (ft_strchr(str, '='))
		return (ft_strchr(str, '=') + 1 - str);
	return (ft_strlen(str) + 1);
}
