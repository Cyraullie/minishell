/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:47:47 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/17 13:26:11 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to increment the shell level
 * 
 * @param env array with the environment variable
 */
void	increment_shlvl(char ***env)
{
	int		content;
	char	*cmd[3];
	char	*shell_content;
	char	*index;

	shell_content = get_env_content("SHLVL", *env);
	content = ft_atoi(shell_content);
	free(shell_content);
	content++;
	cmd[0] = "export";
	cmd[1] = "SHLVL=";
	cmd[2] = NULL;
	index = ft_itoa(content);
	cmd[1] = ft_strjoin(cmd[1], index);
	free(index);
	ft_export(cmd, env);
	free(cmd[1]);
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

/**
 * @brief  function to init all need at start of minishell
 * 
 * @param env array with the environment variable
 * @param envp array with the environment variable come from out
 */
void	init_minishell(char ***env, char **envp)
{
	*env = create_env_array(envp);
	increment_shlvl(env);
	start_history(*env);
	is_child(0);
}
