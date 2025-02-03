/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:16:57 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 17:10:09 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to add not exist environment variable
 * 
 * @param nenv new array of environment variable
 * @param name array contain actual cmd split
 * @param j position in nenv
 */
void	concat_nexistvar(char ***nenv, char **name, int j)
{
	char	*title;

	title = ft_strjoin(name[0], "=");
	title = ft_strjoin(title, name[1]);
	if (!title)
	{
		free(title);
		return ;
	}
	(*nenv)[j] = ft_strdup(title);
	check_tabenv(*nenv, j);
	free(title);
}
//TODO concatenage qui bloque quand on fait une env var qui n'a pas de content
//TODO le set qui bloque quand on fait une env var qui n'a pas de content
/**
 * @brief function to concat existing var with new string
 * 
 * @param env array of environment variable
 * @param nenv new array of environment variable
 * @param name array contain actual cmd split
 * @param j position in nenv
 */
void	concat_existvar(char *env, char ***nenv, char **name, int j)
{
	char	*title;

	if (contain_equal(env))
		env = ft_strjoin(env, "=");
	printf("%s_%d\n", env, contain_equal(env));
	title = ft_strjoin(env, name[1]);
	if (!title)
		return ;
	(*nenv)[j] = ft_strdup(title);
	check_tabenv(*nenv, j++);
	free(title);
}

/**
 * @brief function to handle concat in export
 * 
 * @param env array of environment variable
 * @param nenv new array of environment variable
 * @param name array contain actual cmd split
 */
void	handle_concat(char **env, char ***nenv, char **name)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	name[0][ft_strlen(name[0]) - 1] = '\0';
	while (env[++i])
	{
		if (i != get_envline(env, name[0]))
			dup_env(env, *nenv, i, j);
		else
			concat_existvar(env[i], nenv, name, j);
		j++;
	}
	if (get_envline(env, name[0]) == -1)
		concat_nexistvar(nenv, name, j++);
	*nenv[j] = NULL;
	clean_tab(name);
}
