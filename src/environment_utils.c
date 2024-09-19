/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:25 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/16 08:24:51 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	envp_string_count(char **envp)
{
	size_t	string_count;

	string_count = 0;
	while (envp && envp[string_count])
		string_count++;
	return (string_count);
}

long long	signed_llong_overflow_check(t_var *var, char *n)
{
	size_t		i;
	size_t		max_len;
	int			sign;
	long long	ret;

	i = 0;
	ret = 0;
	sign = 1;
	if (*n == '-')
		sign = -1;
	if (sign == -1 || *n == '+')
		n++;
	max_len = digits_count(LLONG_MAX, 10);
	if (max_len == ft_strlen(n))
		i++;
	while (n[i] >= '0' && n[i] <= '9')
		ret = ret * 10 + (n[i++] - '0');
	ret *= sign;
	if (i == max_len && *n == '9' && \
	(ret > 223372036854775807 || ret < -223372036854775808))
		var->overflow = 1;
	return (ret);
}

int	get_shlvl(t_var *var, char *str)
{
	size_t		i;

	if (!str)
		return (0);
	skip_whitespace(&str);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	var->overflow = 0;
	if (ft_strlen(&str[i]) > digits_count(LLONG_MAX, 10))
	{
		var->overflow = 1;
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (signed_llong_overflow_check(var, str));
}

char	**set_shlvl(t_var *var, char *str)
{
	int		lvl;
	char	envvar_str[BUFFER_SIZE];

	ft_bzero(envvar_str, BUFFER_SIZE);
	ft_strlcpy(envvar_str, "SHLVL=", BUFFER_SIZE);
	lvl = get_shlvl(var, str) + 1;
	str = ft_itoa(lvl);
	if (!str || lvl < 1)
		ft_strlcat(envvar_str, "0", BUFFER_SIZE);
	else if (lvl > 999)
	{
		ft_putstr_fd("warning: shell level (", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
		ft_strlcat(envvar_str, "1", BUFFER_SIZE);
	}
	else
		ft_strlcat(envvar_str, str, BUFFER_SIZE);
	free(str);
	return (command_export(var, envvar_str));
}

int	valid_identifier(t_var *var, char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '=')
		return (invalid_identifier(var, str), false);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (invalid_identifier(var, str), false);
		if (i > 0 && !ft_isalnum(str[i]) && str[i] != '_')
		{
			invalid_identifier(var, str);
			return (false);
		}
		i++;
	}
	return (true);
}
