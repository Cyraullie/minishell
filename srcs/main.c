/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/23 11:27:05 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//TODO check leaks to all buitlins
/**
 * @brief create a modifiable environment variable
 * @param envp , env variable
 * @return NULL on failure, char **env on success
 */
char	**get_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			clean_env(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	char		*cmd[5];
	//char		*cmdd[2];
	//t_command	cmd;

	(void)ac;
	(void)av;
	env = NULL;
	env = get_env(envp);
	//(void)env;
	init_sig();
	cmd[0] = "export";
	cmd[1] = NULL;
	cmd[2] = NULL;
	cmd[3] = NULL;
	/*cmdd[0] = "env";
	cmdd[1] = NULL;*/
	//env = del_line(env, "USER");
	//ft_cd(cmd);
	//ft_pwd(cmdd);
	env = ft_export(cmd, env);
	//ft_env(cmdd, env);
	while (1)
	{
		line = readline("minishell> ");
		handle_eof(line, env);
		//TODO add complete history in .ms_history
		if (line && *line)
			add_history(line);
		//parsing(line, &cmd);
		free(line);
	}
}
