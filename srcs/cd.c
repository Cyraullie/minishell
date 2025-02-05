/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:59 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/05 15:56:00 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to move in different directory
 * 
 * @param cmd command line array
 */
void	ft_cd(char **cmd, char ***env)
{
	char	*userhome;

	userhome = get_userhome();
	if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (free(userhome));
	}
	if (cmd[1] && !ft_strncmp(cmd[1], "~/", 2))
	{
		cmd[1] = ft_strjoin(userhome, ft_strchr(cmd[1], '/'));
		if (!cmd[1])
			return (free(userhome));
	}
	free(userhome);
	ft_chdir(cmd, env);
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
char	*get_userhome(void)
{
	char	*path;
	char	**path_array;
	char	*userhome_path;

	path = get_path();
	path_array = ft_split(path, '/');
	free(path);
	if (!path_array)
		return (NULL);
	userhome_path = ft_strjoin("/home/", path_array[1]);
	if (!userhome_path)
		return (NULL);
	clean_tab(path_array);
	return (userhome_path);
}

/**
 * @brief function to use chdir
 * 
 * @param cmd array of command
 * @param env array of environment variable
 */
void	ft_chdir(char **cmd, char ***env)
{
	char	*path;

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
	path = get_userhome();
	update_oldpwd(get_path(), env);
	chdir(path);
	update_pwd(get_path(), env);
	free(path);
}
