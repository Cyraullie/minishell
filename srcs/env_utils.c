/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:27 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/05 11:19:43 by cgoldens         ###   ########.fr       */
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
	int		id;
	char	**name;

	i = 0;
	id = -1;
	while (env[i])
	{
		name = ft_split(env[i], '=');
		if ((!ft_strncmp(name[0], title, ft_strlen(title))))
			id = i;
		i++;
		clean_tab(name);
	}
	return (id);
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

	i = 0;
	env = NULL;
	while (envp[i])
		i++;
	env = ft_calloc(sizeof(char *) , (i + 1));
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
