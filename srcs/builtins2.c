/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:20:02 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/22 10:18:25 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//TODO export = add variable in env

/**
 * @brief function to unset a selected environment variable
 * 
 * @param cmd get command line array
 * @param env get environment var
 * @return char** the state of the actual environment variable
 */
char	**ft_unset(char **cmd, char **env)
{
	char	**nenv;
	int		i;
	int		j;

	nenv = NULL;
	j = 1;
	while (cmd[j])
	{
		i = 0;
		while (env[i])
			i++;
		if (get_envline(env, cmd[i]) == -1)
			nenv = ft_calloc(sizeof(char *), i + 1);
		else
			nenv = ft_calloc(sizeof(char *), i);
		if (!nenv)
			return (NULL);
		del_envline(env, nenv, cmd[j++]);
		clean_env(env);
		env = nenv;
	}
	return (nenv);
}

/**
 * @brief function to add an environment variable
 * 
 * @param cmd get command line array
 * @param env get environment var
 * @return char** the state of the actual environment variable
 */
char	**ft_export(char **cmd, char **env)
{
	char	**nenv;
	char	**name;
	int		j;

	j = 1;
	nenv = NULL;
	if (!cmd[j])//TODO export tout court = declare -x ZDOTDIR="/home/cgoldens"
		write_env(env);
	while (cmd[j])
	{
		name = ft_split(cmd[j], '=');
		if (!name)
			return (NULL);
		nenv = create_nenv(env, name);
		if (!nenv)
			return (NULL);
		add_envline(env, nenv, cmd[j++], name);
		clean_env(env);
		env = nenv;
	}
	return (nenv);
}
