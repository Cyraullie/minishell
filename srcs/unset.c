/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:00:10 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 16:06:37 by cgoldens         ###   ########.fr       */
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
 * @brief function to delete the choosen line in env var
 * 
 * @param env environment variable
 * @param nenv new environment variable
 * @param title name of the variable 
 */
void	del_envline(char **env, char **nenv, char *title)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 0;
	line = get_envline(env, title);
	while (env[i])
	{
		if (line != i)
		{
			nenv[j] = ft_strdup(env[i]);
			if (!nenv[j])
			{
				clean_tab(nenv);
				return ;
			}
			j++;
		}
		i++;
	}
	nenv[i] = NULL;
}
