/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:05:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/23 16:28:43 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to add a line in env var
 * 
 * @param env environment variable
 * @param nenv new environment variable
 * @param title name of the variable 
 */
void	add_envline(char **env, char **nenv, char *title, char **name)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != get_envline(env, name[0]))
			dup_env(env, nenv, i, j++);
		else
		{
			nenv[j] = ft_strdup(title);
			check_tabenv(nenv, j++);
		}
		i++;
	}
	if (get_envline(env, name[0]) == -1)
	{
		nenv[j] = ft_strdup(title);
		check_tabenv(nenv, j++);
	}
	nenv[j] = NULL;
	clean_env(name);
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

/**
 * @brief check if the name of the env contain special char or digit
 * 
 * @param n name of the env var
 * @return int return state 0 if contain forbiden char and 1 if it's ok
 */
int	check_normenv(char *n)
{
	int			i;
	int			j;
	const char	*sc = "!@#-$\%^&* (){}[]<>?/~`|\\.,:;\"";

	i = 0;
	if (ft_isdigit(n[i]))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (0);
	}
	while (n[i])
	{
		j = 0;
		while (sc[j])
		{
			if (n[i] == sc[j])
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
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
	tab = ft_calloc(sizeof(int *), i + 1);
	if (!tab)
		return ;
	sort_env(env, tab);
	i = -1;
	while (tab[++i] != -1)
	{
		split = ft_split(env[tab[i]], '=');
		if (!split)
			return ;
		printf("declare -x %s=\"%s\"\n", split[0], \
			ft_strchr(env[tab[i]], '=') + 1);
		free(split);
	}
}
