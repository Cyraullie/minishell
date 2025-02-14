/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/14 16:43:51 by cgoldens         ###   ########.fr       */
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
 * @brief  function to init all need at start of minishell
 * 
 * @param env array with the environment variable
 * @param envp array with the environment variable come from out
 */
void	init_minishell(char ***env, char **envp)
{
	*env = create_env_array(envp);
	increment_shlvl(env);
	init_sig();
	start_history(*env);
	is_child(0);
}

/**
 * @brief main function
 * 
 * @param ac count of arguments
 * @param av array of arguments
 * @param envp array with the environment variable come from out
 * @return int return if the program finish successfully or with error
 */
int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_command	*cmd;
	char		**env;

	init_minishell(&env, envp);
	while (ac && av[0])
	{
		cmd = NULL;
		line = readline("minishell> ");
		handle_eof(line, env);
		handle_history(line, env);
		if (!parsing(line, &cmd, &env))
			exec_main(&cmd, &env);
		ft_listdelete(cmd);
	}
	return (0);
}
//TODO if ctrl+D in other minishell no new line with minishell> ??????
//TODO ctrl+c in mineshell child = ko
//TODO avoir un sig_int different pour les enfants