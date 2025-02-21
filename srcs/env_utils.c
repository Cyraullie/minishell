/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:27 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/21 14:34:45 by cgoldens         ###   ########.fr       */
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

//TODO faire une fonction poru get
char	*userpath(char **env)
{
	char	*buf;
	char	*userenv;
	char	**ar_path;
	char	*path;

	userenv = get_env_content("USER", env);
	if (userenv)
		path = ft_strdup_and_free(ft_strjoin("?USER=", userenv));
	else
	{
		buf = ft_calloc(sizeof(char *), BUFFER_SIZE);
		if (!buf)
			return (NULL);
		getcwd(buf, BUFFER_SIZE);
		if (!buf)
			return (NULL);
		ar_path = ft_split(buf, '/');
		free(buf);
		path = ft_strdup_and_free(ft_strjoin("?USER=", ar_path[1]));
		clean_tab(ar_path);
	}
	free(userenv);
	return (path);
}

void	shell_level(char ***env, int *id)
{
	char	*shell_content;
	int		i;
	int		lvl;

	i = *id;
	shell_content = get_env_content("SHLVL", *env);
	if (!shell_content)
	{
		env[0][i++] = ft_strdup("SHLVL=0");
		env[0][i++] = ft_strdup("?SHLVL=1");
	}
	else
	{
		lvl = ft_atoi(shell_content);
		free(shell_content);
		shell_content = ft_itoa(lvl + 1);
		if (get_envline(*env, "?SHLVL") == -1)
			env[0][i++] = ft_strdup_and_free(ft_strjoin("?SHLVL=", \
			shell_content));
		else
			env[0][get_envline(*env, "?SHLVL")] = \
			ft_strdup_and_free(ft_strjoin("?SHLVL=", shell_content));
	}
	free(shell_content);
	*id = i;
}

//TODO si env vide segfault missing SHLVL
/**
 * @brief create a modifiable environment variable
 * @param envp , env variable
 * @return NULL on failure, char **env on success
 */
char	**create_env_array(char **envp)
{
	int		i;
	char	**env;

	i = get_tab_size(envp);
	env = ft_calloc(sizeof(char *), (i + 6));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (clean_tab(env), NULL);
	}
	if (get_envline(env, "?") == -1)
		env[i++] = ft_strdup("?=0");
	env[i++] = userpath(env);
	shell_level(&env, &i);
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
