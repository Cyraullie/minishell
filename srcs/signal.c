/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/21 14:07:05 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief handle signal for SIGINT (Ctrl+C)
 * 
 * @param sig the signal in int
 */
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\nminishell> ", 12);
	}
}

/**
 * @brief handle "signal" for EOF (Ctrl+D)
 * 
 * @param line the line get in readline to catch an EOF
 */

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
		clean_env(env);
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
