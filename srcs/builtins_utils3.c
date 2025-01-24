/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:12:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/24 15:50:53 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to use chdir
 * 
 * @param cmd array of command
 * @param env array of environment variable
 */
void	ft_chdir(char **cmd, char ***env)
{
	(void)env;
	if (cmd[1] && ft_strncmp(cmd[1], "~", 1))
	{
		if (!access(cmd[1], X_OK))
		{
			update_oldpwd(get_path(), env);
			chdir(cmd[1]);
			update_pwd(get_path(), env);
		}
		else if (access(cmd[1], F_OK))
			perror(cmd[1]);
		else
			perror(cmd[1]);
		return ;
	}
	update_oldpwd(get_path(), env);
	chdir(get_userhome());
	update_pwd(get_path(), env);
}

/**
 * @brief function to update PWD with the new position
 * 
 * @param path new postition
 * @param env array of environment variable
 */
void	update_pwd(char *path, char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("PWD=", path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "PWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
}

/**
 * @brief function to update OLDPWD with the old position
 * 
 * @param path old positon
 * @param env array of environment variable
 */
void	update_oldpwd(char *path, char ***env)
{
	int		line;
	char	*cmd[3];
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", path);
	cmd[0] = "export";
	cmd[1] = pwd;
	cmd[2] = NULL;
	line = get_envline(*env, "OLDPWD");
	if (line != -1)
		*env = ft_export(cmd, *env);
	free(pwd);
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
		if (check_normenv(name[0]))
		{
			*nenv = create_nenv(env, name);
			if (!*nenv)
				return (NULL);
			add_envline(env, *nenv, arg, name);
			clean_tab(env);
			env = *nenv;
		}
	}
	else
	{
		*nenv = create_nenv(env, name);
		if (!*nenv)
			return (NULL);
		handle_concat(env, nenv, name);
	}
	return (*nenv);
}

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
