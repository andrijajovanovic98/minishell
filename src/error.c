/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:21:33 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 13:03:15 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_status(t_var *var)
{
	if (errno == 13)
		var->status = 126;
	else if (errno == 2)
		var->status = 127;
	else
		status_1(var);
}

void	error_exec_txt_file(t_var *var)
{
	ft_putendl_fd("Minishell has no script support", STDERR_FILENO);
	free(var->exec_cmd);
	var->exec_cmd = NULL;
	status(var, 2);
}

void	command_not_found(t_var *var)
{
	ft_putstr_fd(var->current->content[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	set_status(var);
}

void	ambiguous_redirect_error(t_var *var, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	set_status(var);
}

void	error_msg(t_var *var, char *str, int status)
{
	ft_putstr_fd(var->current->content[0], STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	var->status = status;
}
