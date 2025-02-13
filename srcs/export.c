/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:20:02 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/13 11:23:19 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to add an environment variable
 * 
 * @param cmd get command line array
 * @param env get environment var
 * @return char** the state of the actual environment variable
 */
int	ft_export(char **cmd, char ***env)
{
	char	**nenv;
	int		j;
	char	**name;

	j = 1;
	if (!cmd[j])
		write_env(*env);
	else
	{
		nenv = NULL;
		while (cmd[j])
		{
			name = split_equal(cmd[j]);
			if (!name || !check_normenv(name[0]))
				return (clean_tab(name), 1);
			nenv = create_nenv(*env, name);
			if (!nenv)
				return (1);
			clean_tab(name);
			handle_export(cmd[j++], *env, &nenv);
			*env = nenv;
		}
		return (0);
	}
	return (0);
}

/**
 * @brief function to write the env sorted alphabetically
 * 
 * @param env array of env elements
 */
void	write_env(char **env)
{
	int		i;
	int		*tab;
	char	**split;

	i = 0;
	while (env[i])
		i++;
	tab = ft_calloc(sizeof(int), i + 1);
	if (!tab)
		return ;
	sort_env(env, tab);
	i = -1;
	while (tab[++i] != -1)
	{
		split = ft_split(env[tab[i]], '=');
		if (!split)
			return ;
		if (split[1])
			printf("declare -x %s=\"%s\"\n", split[0], \
				ft_strchr(env[tab[i]], '=') + 1);
		else
			printf("declare -x %s=\"\"\n", split[0]);
		clean_tab(split);
	}
	free(tab);
}

/**
 * @brief function to handle export "tag"
 * 
 * @param arg string for each element in cmd
 * @param env array of environment variable
 * @param nenv new array of environment variable
 * @return char** return the new env
 */
char	**handle_export(char *arg, char **env, char ***nenv)
{
	char	**name;

	name = split_equal(arg);
	if (!name)
		return (NULL);
	if (name[0][ft_strlen(name[0]) - 1] != '+')
	{
		if (get_tab_size(name) == 1)
		{
			if (check_normenv(name[0]))
				add_envline_without_content(env, *nenv, name);
		}
		else if (check_normenv(name[0]))
			add_envline(env, *nenv, arg, name);
	}
	else
		handle_concat(env, nenv, name);
	clean_tab(env);
	return (*nenv);
}

/**
 * @brief function to duplicate the original env
 * 
 * @param env original environment variable
 * @param nenv new environment variable
 * @param i index for env
 * @param j index for nenv
 */
void	dup_env(char **env, char **nenv, int i, int j)
{
	nenv[j] = ft_strdup(env[i]);
	check_tabenv(nenv, j);
}

/**
 * @brief Create a nenv object for export
 * 
 * @param env environment variable
 * @param name name of the variable 
 * @return char** return new env
 */
char	**create_nenv(char **env, char **name)
{
	int		i;
	char	**nenv;

	i = 0;
	while (env[i])
		i++;
	if (get_envline(env, name[0]) == -1)
		nenv = ft_calloc(sizeof(char *), i + 2);
	else
		nenv = ft_calloc(sizeof(char *), i + 1);
	return (nenv);
}
