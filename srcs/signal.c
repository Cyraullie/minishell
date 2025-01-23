/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/23 09:16:24 by lpittet          ###   ########.fr       */
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

void	handle_eof(char *line, char **env)
{
	if (!line)
	{
		free_tab(env);
		printf("exit\n");
		exit(0);
	}
}

void	init_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
