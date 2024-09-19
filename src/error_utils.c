/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:21:33 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 13:01:03 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	status_1(t_var *var)
{
	if (var->status != 2 && var->status != 126 && var->status != 127)
		var->status = EXIT_FAILURE;
}

void	status(t_var *var, int status)
{
	var->status = status;
}

void	invalid_identifier(t_var *var, char *str)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	var->status = EXIT_FAILURE;
}

void	restore_environment(t_var *var)
{
	perror("Could not change environment");
	malloc_envps_or_exit(var, var->stack_env);
	ft_putendl_fd("Environment has been reset", STDERR_FILENO);
}

void	child_execve_error_handler(t_var *var)
{
	signal(SIGQUIT | SIGINT, SIG_IGN);
	perror(var->exec_cmd);
	free(var->exec_cmd);
	set_status(var);
	free_all(var);
	exit(var->status);
}
