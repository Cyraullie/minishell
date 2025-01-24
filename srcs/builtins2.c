/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:20:02 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 14:47:33 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (get_envline(env, cmd[j]) == -1)
			nenv = ft_calloc(sizeof(char *), i + 1);
		else
			nenv = ft_calloc(sizeof(char *), i);
		if (!nenv)
			return (NULL);
		del_envline(env, nenv, cmd[j++]);
		clean_tab(env);
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
	int		j;

	j = 1;
	nenv = NULL;
	if (!cmd[j])
		write_env(env);
	while (cmd[j])
		handle_export(cmd[j++], env, &nenv);
	return (nenv);
}
