/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:04:40 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 14:37:47 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	command_env(t_var *var)
{
	size_t	i;

	i = 0;
	if (var->current->content[1])
	{
		error_msg(var, ": too many arguments", 1);
		free_all(var);
		exit(var->status);
	}
	while (var->env[i])
	{
		if (!ft_strncmp(var->env[i], "_=", 2))
			print_env_location(var);
		else if (ft_strchr(var->env[i], '='))
			ft_printf("%s\n", var->env[i]);
		i++;
	}
}

char	**command_unset(t_var *var, char *str)
{
	size_t	to_compare;
	size_t	len;
	char	*dest;
	char	**new_env;

	if (!str)
		return (var->env);
	len = envp_string_count(var->env);
	if (!len)
		return (var->env);
	to_compare = 0;
	while (str[to_compare])
		to_compare++;
	dest = malloc(to_compare + 2);
	if (!dest)
		return (free(var->env), NULL);
	ft_strlcpy(dest, str, to_compare + 2);
	ft_strlcpy((dest + to_compare), "=", to_compare + 2);
	new_env = malloc(len * sizeof (char *));
	if (!new_env)
		return (free(var->env), free(dest), NULL);
	if (unset2(var->env, dest, to_compare, new_env))
		return (free(var->env), free(dest), new_env);
	return (free(new_env), free(dest), var->env);
}

int	unset2(char **old_envp, char *dest, size_t to_compare, char **new_env)
{
	int	i;

	i = 0;
	while (old_envp[i])
	{
		new_env[i] = old_envp[i];
		if (ft_strncmp(old_envp[i], dest, to_compare + 1) == 0)
		{
			free(old_envp[i++]);
			while (old_envp[i])
			{
				new_env[i - 1] = old_envp[i];
				i++;
			}
			new_env[i - 1] = NULL;
			return (true);
		}
		i++;
	}
	return (false);
}

char	**change_var(char **env, char *str)
{
	char	*var;
	size_t	len;
	size_t	i;

	len = to_export_len(str);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, len) || \
		(ft_strncmp(env[i], str, len) == - '=' && !ft_strchr(env[i], '=')))
		{
			var = ft_strdup(str);
			if (!var)
				return (free_string_array(env), NULL);
			free(env[i]);
			env[i] = var;
			return (env);
		}
	}
	return (env);
}

char	**command_export(t_var *var, char *str)
{
	char	**new_envp;
	size_t	len;
	size_t	i;

	if (!valid_identifier(var, str))
		return (var->env);
	if (existing_env_var(var->env, str))
		return (change_var(var->env, str));
	len = envp_string_count(var->env);
	new_envp = malloc((len + 1 + 1) * sizeof (char *));
	if (!new_envp)
		return (free_string_array(var->env), NULL);
	i = -1;
	while (++i < len)
		new_envp[i] = var->env[i];
	free(var->env);
	new_envp[i] = ft_strdup(str);
	if (!str)
		return (free(new_envp), NULL);
	new_envp[i + 1] = NULL;
	return (new_envp);
}
