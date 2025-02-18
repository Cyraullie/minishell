/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:57:59 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/18 17:04:17 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief function to move in different directory
 * 
 * @param cmd command line array
 * @return int return success or failed
 */
int	ft_cd(char **cmd, char ***env)
{
	char	*userhome;

	userhome = get_userhome(*env);
	if (!cmd[1])
		cmd[1] = userhome;
	else if (cmd[1] && !ft_strncmp(cmd[1], "~/", 2))
	{
		cmd[1] = ft_strjoin(userhome, ft_strchr(cmd[1], '/'));
		if (!cmd[1])
			return (free(userhome), 1);
	}
	else if (cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (free(userhome), 1);
	}
	ft_chdir(cmd, env);
	free(userhome);
	return (0);
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
	path = get_userhome(*env);
	update_oldpwd(get_path(), env);
	chdir(path);
	update_pwd(get_path(), env);
	free(path);
}
