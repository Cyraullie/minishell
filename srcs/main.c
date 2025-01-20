/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/20 14:05:28 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env[i] = ft_strdup(envp[i]);
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
	//t_command	cmd;

	(void)ac;
	(void)av;
	env = get_env(envp);
	(void)env;
	init_sig();
	cmd[0] = "pwd";
	cmd[1] = NULL;
	//cmd[1] = "test";
	cmd[2] = NULL;
	cmd[3] = NULL;
	cmd[4] = NULL;
	ft_pwd(cmd);
	while (1)
	{
		line = readline("minishell> ");
		handle_eof(line);
		if (line && *line)
			add_history(line);
		//parsing(line, &cmd);
		free(line);
	}
}
