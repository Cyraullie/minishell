/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:47:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/12 15:49:57 by cgoldens         ###   ########.fr       */
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
		write(1, "\n", 1);
		if (is_child(-1) == 0)
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
 * @brief function to init all signal we need
 * 
 */
void	init_sig(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&sq, sizeof(sq));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sq.sa_handler = SIG_IGN;
	sq.sa_flags = 0;
	sigemptyset(&sq.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

int	is_child(int status)
{
	static int	bool = 0;

	if (status == -1)
		return (bool);
	else
		bool = status;
	return (bool);
}
