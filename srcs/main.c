/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/24 16:47:00 by cgoldens         ###   ########.fr       */
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
			clean_tab(env);
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
	t_command	*cmd;
	char		**env;

	(void)ac;
	(void)av;
	env = get_env(envp);
	init_sig();
	start_history();
	while (1)
	{
		cmd = NULL;
		line = readline("minishell> ");
		handle_eof(line, env);
		handle_history(line);
		parsing(line, &cmd, env);
		//TODO exec builtins exec(&cmd, env);
		ft_listdelete(cmd);
	}
	return (ft_strlen(env[0]));
}
