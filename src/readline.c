/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:36:13 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/20 18:00:36 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_var(t_var *var, int argc, char **argv, char **envp)
{
	setup_signal_handlers(var);
	(void)argc;
	(void)argv;
	var->stack_env = envp;
	var->tokens = NULL;
	var->last_token = NULL;
	var->current = NULL;
	var->list = NULL;
	var->line = NULL;
	var->env = NULL;
	var->splitted_path = NULL;
	var->hd_history = NULL;
	var->prompt = NULL;
	var->exec_cmd = NULL;
	ft_bzero(var->stack_prompt, 4);
	ft_strlcpy(var->stack_prompt, " > ", 4);
	var->cwd = getcwd(NULL, 0);
	malloc_envps_or_exit(var, envp);
	var->status = 0;
	var->loop = true;
}

void	check_received_signal(t_var *var)
{
	extern sig_atomic_t	g_signal;

	if (g_signal)
	{
		var->status = g_signal + 128;
		g_signal = 0;
	}
}

char	*trim_nl_free(char *line)
{
	char	*trim;

	trim = ft_strtrim(line, "\n");
	free(line);
	return (trim);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	init_var(&var, argc, argv, envp);
	while (var.loop)
	{
		if (TESTER || !isatty(STDIN_FILENO))
			var.line = trim_nl_free(get_next_line(STDIN_FILENO));
		else
			var.line = readline(PROMPT);
		if (!var.line)
			break ;
		sigint_handler_non_interactive_mode(&var);
		var.tokens = tokenize(&var);
		if (parse_tokens(&var) == true)
			execute(&var);
		if (var.line && *var.line)
			add_history(var.line);
		exec_cleanup(&var);
		sigint_handler_interactive_mode(&var);
	}
	if (!TESTER && isatty(STDIN_FILENO))
		ft_printf("exit\n");
	rl_clear_history();
	free_all(&var);
	return (var.status);
}
