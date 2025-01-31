/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:35:36 by lpittet           #+#    #+#             */
/*   Updated: 2025/01/31 15:11:13 by cgoldens         ###   ########.fr       */
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

char	*my_getenv(char *var_name, char **env)
{
	int	ienv;
	int	i;

	ienv = get_envline(env, var_name);
	if (ienv == -1)
		return (NULL);
	i = 0;
	while (env[ienv][i] != '=')
		i++;
	return (ft_substr(env[ienv], i + 1, ft_strlen(env[ienv])));
}

void	increment_shlvl(char ***env)
{
	int		content;
	char	*cmd[3];

	content = ft_atoi(my_getenv("SHLVL", *env));
	content++;
	cmd[0] = "export";
	cmd[1] = "SHLVL=";
	cmd[2] = NULL;
	cmd[1] = ft_strjoin(cmd[1], ft_itoa(content));
	*env = ft_export(cmd, *env);
}

void	init_minishell(char ***env, char **envp)
{
	*env = get_env(envp);
	increment_shlvl(env);
	init_sig();
	start_history(*env);
}

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
