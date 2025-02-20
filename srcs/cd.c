/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:59 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/20 14:18:48 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO cd "file: Not a directory" if file and not dir
/**
 * @brief function to move in different directory
 * 
 * @param cmd command line array
 * @return int return success or failed
 */
int	ft_cd(char **cmd, char ***env)
{
	char	*userhome;
	char	*path;
	int		exitv;

	path = ft_strdup(cmd[1]);
	userhome = get_userhome(*env);
	if (get_tab_size(cmd) == 1)
		path = ft_strdup(userhome);
	else if (cmd[1][0] == 0)
		return (free(userhome), 0);
	else if (cmd[1] && !ft_strncmp(cmd[1], "~/", 2))
	{
		free(path);
		path = ft_strjoin(userhome, ft_strchr(cmd[1], '/'));
		if (!path)
			return (free(userhome), 1);
	}
	else if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (free(userhome), 1);
	}
	exitv = ft_chdir(path, env, userhome);
	free(path);
	return (exitv);
}

/**
 * @brief Get the path object
 * 
 * @return char* path
 */
char	*get_path(void)
{
	char	*p;

	p = ft_calloc(sizeof(char *), BUFFER_SIZE);
	if (!p)
		return (NULL);
	getcwd(p, BUFFER_SIZE);
	if (!p)
		return (NULL);
	return (p);
}

/**
 * @brief Get the userhome object
 * 
 * @return char* userhome path
 */
char	*get_userhome(char **env)
{
	char	*userhome_path;
	char	*user;

	user = get_env_content("?USER", env);
	if (!user)
		return (NULL);
	userhome_path = ft_strjoin("/home/", user);
	if (!userhome_path)
		return (NULL);
	free(user);
	return (userhome_path);
}

/**
 * @brief function to use chdir
 * 
 * @param cmd array of command
 * @param env array of environment variable
 */
int	ft_chdir(char *path, char ***env, char *userhome)
{
	if (path && ft_strncmp(path, "~", 1))
	{
		if (!access(path, X_OK))
		{
			update_oldpwd(get_path(), env);
			chdir(path);
			update_pwd(get_path(), env);
		}
		else if (access(path, F_OK))
		{
			free(userhome);
			return (perror(path), 1);
		}
		else
		{
			free(userhome);
			return (perror(path), 1);
		}
		return (free(userhome), 0);
	}
	update_oldpwd(get_path(), env);
	chdir(userhome);
	update_pwd(get_path(), env);
	free(userhome);
	return (0);
}
