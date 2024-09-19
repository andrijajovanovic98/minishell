/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:46:32 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 17:25:53 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_system_commands(t_var *var)
{
	var->exec_cmd = NULL;
	var->splitted_path = splitted_path(var);
	if (ft_strchr(var->current->content[0], '/')
		|| !var->current->content[0][0])
		var->exec_cmd = check_given_file(var);
	else
		var->exec_cmd = get_cmd(var);
	if (!var->exec_cmd)
		return (free_all(var), exit(var->status));
	signal(SIGQUIT | SIGINT, SIG_DFL);
	execve(var->exec_cmd, var->current->content, var->env);
	child_execve_error_handler(var);
}

void	exec_other_commands(t_var *var)
{
	var->current = get_next_node(var->list, CMD, END);
	if (!var->current)
	{
		free_all(var);
		exit(EXIT_SUCCESS);
	}
	update_last_cmd(var);
	if (ft_strncmp(var->current->content[0], "echo", 5) == 0)
		command_echo(var);
	else if (ft_strncmp(var->current->content[0], "env", 4) == 0)
		command_env(var);
	else if (ft_strncmp(var->current->content[0], "pwd", 4) == 0)
		command_pwd(var);
	else
		exec_system_commands(var);
	free_all(var);
	exit(EXIT_SUCCESS);
}

int	cd_export_exit_or_unset(t_var *var)
{
	if (ft_strncmp(var->current->content[0], "export", 7) == 0)
		var->env = env_loop(var, &command_export);
	else if (ft_strncmp(var->current->content[0], "unset", 6) == 0)
		var->env = env_loop(var, &command_unset);
	else if (ft_strncmp(var->current->content[0], "cd", 3) == 0)
	{
		if (!too_many_arguments(var, var->current))
			command_cd(var, var->current->content[1]);
	}
	else if (ft_strncmp(var->current->content[0], "exit", 5) == 0)
		command_exit(var);
	else
		return (false);
	if (!var->env)
		restore_environment(var);
	return (true);
}

void	one_simple_cmd(t_var *var)
{
	var->current = var->list;
	update_last_cmd(var);
	if (!open_files_in_parent(var))
		return (status_1(var));
	var->current = get_next_node(var->list, CMD, END);
	if (!var->current)
		return ;
	if (cd_export_exit_or_unset(var))
		return ;
	var->pid = fork();
	if (var->pid == -1)
		return (perror("fork"), status(var, FORK_ERROR), free_all(var));
	if (var->pid == 0)
	{
		var->current = var->list;
		redirect_or_exit(var);
		exec_other_commands(var);
	}
	wait_children(var);
}

void	execute(t_var *var)
{
	int	i;

	var->last_status = var->status;
	var->status = EXIT_SUCCESS;
	if (!write_here_docs(var))
		return ;
	var->cmds = count_node_types(var->list, PIPE | END);
	if (var->cmds == 1)
		return (one_simple_cmd(var));
	i = 0;
	while (i < var->cmds)
	{
		if (i == 0)
			first_cmd(var);
		else if (i == var->cmds - 1)
			last_cmd(var);
		else
			middle_cmd(var);
		if (var->status)
			var->cmds = i;
		i++;
	}
	wait_children(var);
}
