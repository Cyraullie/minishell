/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:05:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/22 10:26:07 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO faire un tri a -> z pour les titres des variables
//TODO mettre le texte apres le = entre guillment (dexlare -x bla="bla")
/**
 * @brief 
 * 
 * @param env 
 */
void	write_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i++]);
	}
}

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
