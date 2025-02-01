/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:47:55 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/01 14:25:31 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	i = 0;
	j = 0;
	name[0][ft_strlen(name[0]) - 1] = '\0';
	while (env[i])
	{
		if (i != get_envline(env, name[0]))
			dup_env(env, *nenv, i, j++);
		else
			concat_existvar(env[i], nenv, name, j++);
		i++;
	}
	if (get_envline(env, name[0]) == -1)
		concat_nexistvar(nenv, name, j++);
	*nenv[j] = NULL;
	clean_tab(name);
}

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

	title = ft_strjoin(env, name[1]);
	if (!title)
		return ;
	(*nenv)[j] = ft_strdup(title);
	check_tabenv(*nenv, j++);
	free(title);
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

char	*my_getenv(char *var_name, char **env)
{
	int	ienv;
	int	i;

	ienv = get_envline(env, var_name);
	if (ienv == -1)
		return (NULL);
	i = 0;
	while (env[ienv][i] != '=')
		i++;
	return (ft_substr(env[ienv], i + 1, ft_strlen(env[ienv])));
}
