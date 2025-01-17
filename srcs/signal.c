/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/17 16:13:27 by cgoldens         ###   ########.fr       */
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

void	handle_eof(char *line)
{
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
}

void	init_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}