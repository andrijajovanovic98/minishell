/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils9000.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:38:30 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 17:28:48 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_getenv_get_envvar_name(char *s, char **var, char *tmp, size_t len)
{
	if (*var)
	{
		*tmp = **var;
		**var = 0;
	}
	else
	{
		*tmp = 0;
		*var = s + len;
	}
}

void	print_env_location(t_var *var)
{
	var->splitted_path = splitted_path(var);
	if (search_path(var, X_OK) || search_path(var, F_OK))
		ft_printf("_=%s\n", var->exec_cmd);
	free(var->exec_cmd);
}

char	*ft_getenv(char **env, char *s)
{
	size_t	i;
	size_t	len;
	char	*var;
	char	tmp;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (env[i])
	{
		var = ft_strchr(env[i], '=');
		ft_getenv_get_envvar_name(s, &var, &tmp, len);
		if (ft_strlen(env[i]) == len && !ft_strncmp(s, env[i], len + 1))
		{
			*var = tmp;
			if (*var == '=')
				var++;
			return (var);
		}
		*var = tmp;
		i++;
	}
	return (NULL);
}

void	write_or_exit(t_var *var, int fd, const void *buf, size_t n)
{
	if (write(fd, buf, n) == -1)
	{
		perror("write");
		free_all(var);
		exit(EXIT_FAILURE);
	}
}
