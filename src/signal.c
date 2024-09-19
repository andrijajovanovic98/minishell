/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:36:22 by ajovanov          #+#    #+#             */
/*   Updated: 2024/08/20 16:15:32 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

sig_atomic_t	g_signal = 0;

void	handle_sigint(int sig)
{
	g_signal = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	save_sigint(int signal)
{
	g_signal = signal;
}

void	sigint_handler_non_interactive_mode(t_var *var)
{
	var->sa.sa_handler = save_sigint;
	sigaction(SIGINT, &var->sa, NULL);
}

void	sigint_handler_interactive_mode(t_var *var)
{
	var->sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &var->sa, NULL);
}

void	setup_signal_handlers(t_var *var)
{
	signal(SIGQUIT, SIG_IGN);
	var->sa.sa_flags = SA_RESTART;
	sigemptyset(&var->sa.sa_mask);
	sigint_handler_interactive_mode(var);
}
