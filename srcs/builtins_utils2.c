/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:05:36 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/21 17:20:46 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO faire un tri a -> z pour les titres des variables
//TODO mettre le texte apres le = entre guillment (dexlare -x bla="bla")
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

void	dup_env(char **env, char **nenv, int i, int j)
{
	nenv[j] = ft_strdup(env[i]);
	check_tabenv(nenv, j);
}
