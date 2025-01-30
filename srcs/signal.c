/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/30 13:33:08 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

sig_atomic_t	g_stop = 0;

/**
 * @brief handle signal for SIGINT (Ctrl+C)
 * 
 * @param sig the signal in int
 */
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_stop = 1;
		write(STDOUT_FILENO, "\nminishell> ", 12);
	}
}

/**
 * @brief handle "signal" for EOF (Ctrl+D)
 * 
 * @param line the line get in readline to catch an EOF
 * @param env the environment variable
 */
void	handle_eof(char *line, char **env)
{
	if (!line)
	{
		g_stop = 0;
		clean_tab(env);
		free(line);
		printf("exit\n");
		exit(0);
	}
}

/**
 * @brief function to init all signal we need
 * 
 */
void	init_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
