/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:27 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/13 11:22:55 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Get the line in env
 * 
 * @param env environment variable
 * @param title name of the variable
 * @return int state if the line are find
 */
int	get_envline(char **env, char *title)
{
	int		i;
	char	**name;

	i = -1;
	while (env[++i])
	{
		name = ft_split(env[i], '=');
		if ((!ft_strncmp(name[0], title, ft_strlen(title) + 1)))
		{
			clean_tab(name);
			return (i);
		}
		clean_tab(name);
	}
	return (-1);
}

/**
 * @brief create a modifiable environment variable
 * @param envp , env variable
 * @return NULL on failure, char **env on success
 */
char	**create_env_array(char **envp)
{
	int		i;
	char	**env;
	char	*shell_content;

	i = 0;
	env = NULL;
	while (envp[i])
		i++;
	env = ft_calloc(sizeof(char *), (i + 5));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (clean_tab(env), NULL);
	}
	env[i++] = ft_strdup("?=0");
	shell_content = get_env_content("SHLVL", env);
	if (!shell_content)
		env[i++] = ft_strdup("SHLVL=1");
	env[i] = NULL;
	return (free(shell_content), env);
}

/**
 * @brief Get the env content object
 * 
 * @param var_name 
 * @param env 
 * @return char* 
 */
char	*get_env_content(char *var_name, char **env)
{
	int		ienv;
	int		i;
	char	*content;

	ienv = get_envline(env, var_name);
	if (ienv == -1)
		return (NULL);
	i = 0;
	while (env[ienv][i] != '=')
		i++;
	content = ft_substr(env[ienv], i + 1, ft_strlen(env[ienv]));
	return (content);
}
