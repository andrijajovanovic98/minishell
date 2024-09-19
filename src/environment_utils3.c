/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:24:11 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 17:48:46 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	existing_env_var(char **env, char *str)
{
	char	*tmp;
	char	*var;

	tmp = ft_strchr(str, '=');
	if (!tmp)
	{
		var = ft_getenv(env, str);
	}
	else
	{
		tmp[0] = '\0';
		var = ft_getenv(env, str);
		tmp[0] = '=';
	}
	return (var != NULL);
}

char	*last_arg(char **args)
{
	size_t	i;

	i = 0;
	while (args[i] && args[i + 1])
		i++;
	return (args[i]);
}

void	update_last_cmd(t_var *var)
{
	t_node	*cmd;
	char	*str;
	char	*envvar;

	cmd = get_next_node(var->current, CMD, PIPE | END);
	if (!cmd)
		str = NULL;
	else
		str = last_arg(cmd->content);
	envvar = ft_strjoin_nofree("_=", str);
	if (!envvar)
		return (perror("update _"));
	var->env = command_export(var, envvar);
	free(envvar);
	if (!var->env)
		restore_environment(var);
}

void	initialize_environment(t_var *var)
{
	char	*str;
	char	*path;

	str = ft_getenv(var->env, "SHLVL");
	var->env = set_shlvl(var, str);
	if (!var->env)
		return (perror("exiting"), free_all(var), exit(EXIT_FAILURE));
	str = ft_getenv(var->env, "PWD");
	if (!str && var->cwd)
		update_env_after_cd(var, "PWD=", var->cwd);
	str = ft_getenv(var->env, "PATH");
	path = ft_strdup(ENV_PATH);
	if (!str && path)
		var->env = command_export(var, path);
	free(path);
	if (!var->env)
		return (perror("exiting"), free_all(var), exit(EXIT_FAILURE));
}

void	malloc_envps_or_exit(t_var *var, char **envp)
{
	size_t	len;
	size_t	i;

	len = envp_string_count(envp);
	var->env = malloc((len + 1) * sizeof (char *));
	if (!var->env)
		return (perror("exiting"), free_all(var), exit(EXIT_FAILURE));
	i = 0;
	while (i < len)
	{
		var->env[i] = ft_strdup(envp[i]);
		if (!var->env[i])
			return (perror("exiting"), free_all(var), exit(EXIT_FAILURE));
		i++;
	}
	var->env[i] = NULL;
	initialize_environment(var);
}
