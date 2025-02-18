/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:34:34 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/18 15:54:09 by cgoldens         ###   ########.fr       */
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
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
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
	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sq.sa_handler = handle_sigint_heredoc;
	sq.sa_flags = SA_RESTART;
	sigemptyset(&sq.sa_mask);
	sigaction(SIGQUIT, &sq, NULL);
}
