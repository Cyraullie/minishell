/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:32:33 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/03 16:46:44 by cgoldens         ###   ########.fr       */
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

	i = -1;
	j = 0;
	while (env[++i])
	{
		if (i != get_envline(env, name[0]))
			dup_env(env, nenv, i, j++);
		else
		{
			nenv[j] = ft_strdup(title);
			check_tabenv(nenv, j++);
		}
	}
	if (get_envline(env, name[0]) == -1)
	{
		nenv[j] = ft_strdup(title);
		check_tabenv(nenv, j++);
	}
	nenv[j] = NULL;
	clean_tab(name);
}

void	add_envline_without_content(char **env, char **nenv, char **name)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
		dup_env(env, nenv, i, j++);
	if (get_envline(env, name[0]) == -1)
	{
		nenv[j] = ft_strdup(name[0]);
		check_tabenv(nenv, j++);
	}
	nenv[j] = NULL;
	clean_tab(name);
}

/**
 * @brief function to handle multiple equal in env value
 * 
 * @param a_str array of all value in env line split by equal
 * @return char* return the env value
 */
char	*multiple_equal(char **a_str)
{
	int		i;
	char	*name;

	i = 0;
	name = "";
	while (a_str[++i])
	{
		name = ft_strjoin(name, a_str[i]);
		name = ft_strjoin(name, "=");
		if (!name)
			return (NULL);
	}
	return (name);
}

/**
 * @brief function to handle split with multiple equal in env value
 * 
 * @param str line of env var
 * @return char** return an array for name and value
 */
char	**split_equal(char *str)
{
	char	**a_str;
	int		i;
	char	**f_str;

	a_str = ft_split(str, '=');
	if (a_str[2])
	{
		i = 0;
		f_str = ft_calloc(sizeof(char *), 3);
		f_str[i] = ft_strdup(a_str[i]);
		if (!f_str[0])
		{
			free(f_str);
			return (NULL);
		}
		f_str[1] = multiple_equal(a_str);
		if (!f_str[1])
		{
			free(f_str);
			return (NULL);
		}
	}
	return (a_str);
}
