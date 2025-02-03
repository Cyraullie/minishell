/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/02/03 16:32:02 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO check leaks to all buitlins
//TODO fix norme
//TODO sort file and function for better visibility
/**
 * @brief 
 * 
 * @param env 
 */
void	increment_shlvl(char ***env)
{
	int		content;
	char	*cmd[3];

	content = ft_atoi(get_env_content("SHLVL", *env));
	content++;
	cmd[0] = "export";
	cmd[1] = "SHLVL=";
	cmd[2] = NULL;
	cmd[1] = ft_strjoin(cmd[1], ft_itoa(content));
	*env = ft_export(cmd, *env);
}

/**
 * @brief 
 * 
 * @param env 
 * @param envp 
 */
void	init_minishell(char ***env, char **envp)
{
	*env = create_env_array(envp);
	increment_shlvl(env);
	init_sig();
	start_history(*env);
}

/**
 * @brief 
 * 
 * @param ac 
 * @param av 
 * @param envp 
 * @return int 
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
		if (g_stop)
		{
			free(line);
			line = NULL;
			g_stop = 0;
			continue ;
		}
		handle_history(line, env);
		parsing(line, &cmd, env);
		exec_built(&cmd, &env);
		ft_listdelete(cmd);
	}
	return (0);
}
