/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/18 13:54:16 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

/**
 * @brief handle signal for SIGINT (Ctrl+C)
 * 
 * @param sig the signal in int
 */
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_interrupted = 1;
		write(1, "\n", 1);
		if (is_child(-1) == 0 || is_child(-1) == 2)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		if (is_child(-1) == 0 || is_child(-1) == 2)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
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
		clean_tab(env);
		free(line);
		printf("exit\n");
		exit(0);
	}
}

/**
 * @brief 
 * 
 * @param status 
 * @return int 
 */
int	is_child(int status)
{
	static int	bool = 0;

	if (status == -1)
		return (bool);
	else
		bool = status;
	return (bool);
}

/**
 * @brief Set the up signals parent object to ignore
 * 
 */
void	setup_signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
