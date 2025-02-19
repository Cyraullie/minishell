/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:34:34 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/19 14:22:25 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param sig 
 */
void	handle_sigint_heredoc(int sig)
{
	g_heredoc_interrupted = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}

/**
 * @brief Set the up signals heredoc object
 * 
 */
void	setup_signals_heredoc(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&sq, sizeof(sq));
	sq.sa_handler = SIG_IGN;
	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

void	setup_sigquit_heredoc(void)
{
}
